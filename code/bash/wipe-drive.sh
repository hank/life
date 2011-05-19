#!/bin/bash
# Wipe Drive - Written by Kent Overstreet

DEV=$1

if [ ! -b "$DEV" ]; then
	echo "Can't open $DEV"
	exit 1
fi

SECTORS=`hdparm -I "$DEV"|awk '/LBA48/ { print $5 }'`
OFFSET=0

echo "$DEV has $SECTORS sectors:"

while (($SECTORS)); do
	i=$(( $SECTORS > 65535 ? 65535 : $SECTORS ))

	echo "wiping $i sectors at offset $OFFSET"
	hdparm --please-destroy-my-drive --trim-sector-ranges $OFFSET:$i $DEV

	SECTORS=$(($SECTORS - $i))
	OFFSET=$(($OFFSET + $i))
done
