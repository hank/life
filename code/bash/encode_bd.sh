#! /bin/bash

# =====================================================================
# Blu-ray encoding script by HyRax February 2009 http://www.serenux.com
# =====================================================================

# Make sure the user has specified what to work on.
if [ -z "$1" -o -z "$2" ]; then
  echo "-----------------------------"
  echo "Blu-ray movie encoding script"
  echo "-----------------------------"
  echo "Written by HyRax February 2009"
  echo "http://www.serenux.com"
  echo "Usage: $0 <m2ts file without extension> <1080p|720p>"
  echo "Example: If your 720p movie file is called TheDarkKnight.m2ts and then"
  echo "your usage will be: $0 TheDarkKnight 720p"
  echo
  exit
fi

# Get the width and height based on the source type
if [ "$2" == "720p" ]; then
width="1280"
height="720"
bitrate="4000"
ref="6"
elif [ "$2" == "1080p" ]; then
width="1920"
height="1080"
bitrate="6000"
ref="4"
else
  echo "Invalid source type."
  echo
  exit
fi

# The crf=21 option controls encoding quality, and indirectly the final
# filesize. The higher the value, the more compression and thus smaller
# file size. Reduce the value and file size will go up. A value of 21
# should produce a file of approximately 4GB in size for a typical movie.

# Encode the video using x264, ignore the audio for now.

# NOTES on x264encopts
# - Bluray limits the max bframes to 3
# - crf of 19-21.5 is good.
# - ref can affect playback in consumer devices.  Level 4.1 gives max refs
#   for 720p and 1080p of 9 and 4 respectively
# - bpyramid should be set to normal unless targeting BluRay devices.
# - crf is incompatible with 2pass.

echo "RUNNING FIRST PASS"
mencoder $1.m2ts \
-nosound \
-ovc x264 \
-of rawvideo \
-x264encopts ref=$ref:bframes=3:b_pyramid=1:trellis=2:analyse=all:8x8dct=1:me=umh:merange=32:direct=auto:threads=auto:turbo=1:pass=1:bitrate=$bitrate:subq=1:frameref=3 \
-passlogfile $1_2pass.log \
 -o /dev/null
if [ $? -ne 0 ]; then
  echo "First pass failed."
  exit
fi

echo "RUNNING SECOND PASS"
mencoder $1.m2ts \
-nosound \
-ovc x264 \
-of rawvideo \
-x264encopts ref=$ref:bframes=3:b_pyramid=1:trellis=2:analyse=all:8x8dct=1:me=umh:merange=32:direct=auto:threads=auto:pass=2:bitrate=$bitrate:subq=6:frameref=3 \
-passlogfile $1_2pass.log \
-o $1.$2.x264
if [ $? -ne 0 ]; then
  echo "Second pass failed."
  exit
fi


# Dump the first original audio track (should be the English track) but
# don't re-encode it. Ignore the video.
mplayer $1.m2ts -dumpaudio -dumpfile $1.$2.ac3
if [ $? -ne 0 ]; then
  echo "Audio pass failed."
  exit
fi

# Copy the raw x264 encoded video into an MP4 container so we can set
# the correct framerate (generally 23.976 - adjust it if MPlayer or
# MEncoder report something different)
MP4Box -add $1.$2.x264 $1.$2.mp4 -fps 23.976
if [ $? -ne 0 ]; then
  echo "Container failed."
  exit
fi

# Finally, merge everything into a single MKV file
mkvmerge -o $1.$2.mkv $1.mp4 --track-name 0:Eng $1.$2.ac3
if [ $? -ne 0 ]; then
  echo "Mux failed."
  exit
fi

# Remove the hash in front of the next command to have the script delete
# your working files when encoding is complete.
# rm $1.m2ts $1.x264 $1.ac3

# Tell the user we're done.
echo "All done! Your final movie file is called $1.$2.mkv - enjoy!"
