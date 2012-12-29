#!/bin/bash
OFFSET=1
TMPFILES=
THUMBS= 
THUMBIDX=1
OUT=bc-coin-page.png
for i in $@; do
  THUMB="${i%.png}.thumb.png"
  convert $i -resize 300x label:${i} -gravity center -append $THUMB
  THUMBS[$THUMBIDX]="$THUMB"
  THUMBIDX=$(($THUMBIDX+1))
done
while [ $OFFSET -lt ${#THUMBS[@]} ]; do
  FILES=${THUMBS[@]:OFFSET:10}
  TMPFILE=`mktemp -u bc-coin-gen.XXXXXXX`.png
  touch $TMPFILE
  convert $FILES +append $TMPFILE
  TMPFILES="$TMPFILES $TMPFILE"
  OFFSET=$(($OFFSET + 10))
done
convert $TMPFILES -append $OUT
rm -f $TMPFILES $THUMBS
