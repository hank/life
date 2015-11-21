#!/bin/bash
NAME=$1
ISO=$2
BASE="/opt/VirtualBox VMs"
VDI="${BASE}/${NAME}.vdi"
vboxmanage createvm --name $NAME --ostype Debian --register --basefolder "${BASE}"
vboxmanage modifyvm $NAME --memory 256 --acpi on --boot1 dvd --nic1 bridged --bridgeadapter1 eth0 --vrdeport 3389
vboxmanage createhd --filename "${VDI}" --size 10000 --format VDI
vboxmanage storagectl $NAME --name "SATA Controller" --add sata --controller IntelAhci
vboxmanage storageattach $NAME --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium "${VDI}"
vboxmanage storagectl $NAME --name "IDE Controller" --add ide
vboxmanage storageattach $NAME --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium $ISO
vboxmanage modifyvm $NAME --boot1 dvd
vboxmanage modifyvm $NAME --chipset piix3 --ioapic off --nic1 bridged --audio none --vrde on
vboxmanage modifyvm $NAME --longmode on
echo "Run vboxheadless -s ${NAME}"
