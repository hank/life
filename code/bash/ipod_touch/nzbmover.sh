#!/bin/bash
IDENTITY_FILE=/var/root/.ssh/id_rsa
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
LOG=/var/log/nzbmover
DEST_FILE=iPodTouch_`date +%Y%m%d_%H:%M:%S`.nzb
DEST=ralree.dyndns.org:/nexus/tardis/hellanzb/nzb/daemon.queue/$DEST_FILE
PORT=22000
USER=hank
DIR=/var/mobile/Library/Downloads/

echo "Checking for changes in $DIR" >> $LOG
/usr/bin/find $DIR -type f | while read f
do
	if [[ ${f##*.} == "mp3" ]]; then
		#echo "$f is an mp3.  Moving on!"
		continue
	fi
        grep -i -m 1 -E "^<nzb" "$f" 2>&1 > /dev/null
        IS_NZB=$?
        if [ $IS_NZB -eq 0 ]; then
                echo "  NZB file detected: $f" >> $LOG
                scp -P $PORT "$f" ${USER}@${DEST} 2>&1 >> $LOG
                if [ $? -eq 0 ]; then
                        echo "  File sent, removing" >> $LOG
                        rm "$f"
                        break
                fi
        fi
done
