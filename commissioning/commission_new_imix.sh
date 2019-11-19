#!/usr/bin/env bash

me=`basename "$0"`

if [[ $# -ne 1 ]]; then
	echo "You must supply the imix ID as the argument to this script."
	echo "Example: $me c098e5140001"
	echo ""
	echo "Script expects USB attached to start."
	exit 1
fi

idnocolon=$1
idcolon=`echo $1 | sed 's/\(..\)/\1:/g;s/:$//'`


echo "Configuring this imix with ID: $1"
echo ""

echo "Configuring the FTDI with imix parameters..."
sudo ./ftx_prog --manufacturer MostlyTyped --product "imix IoT Module - TockOS" --new-serial-number $idnocolon 
rc=$?;
if [[ $rc != 22 ]]; then
	echo "Error programming FTDI"
	exit 2
fi
echo "done"

echo ""
echo "Finished configuring FTDI."
echo "Unplug USB from debug to target."
read -n1 -r -p "Press any key to continue..." key
echo ""
echo "Connect JTAG to the MCU port."
read -n1 -r -p "Press any key to continue..." key
echo ""

echo "Flashing the bootloader using JTAG..."
tockloader flash imix_bootloader.bin --address 0 --jlink-device ATSAM4LC8C --arch cortex-m4 --board imix --jlink
echo "done"

echo "Setting the id attribute..."
tockloader set-attribute --arch cortex-m4 --board imix --jlink id $idnocolon
echo "done"

echo "Setting the appaddr attribute..."
tockloader set-attribute --arch cortex-m4 --board imix --jlink appaddr 0x40000
echo "done"

echo "Ensuring the submodule for Tock is checked out"
git submodule update --init --recursive tock

echo "Flashing the imix kernel"
pushd tock/boards/imix
make flash
popd
echo "done"

echo "Flashing the imix app"
pushd libtock-c/examples/tests/imix
make
tockloader install --make --jlink --erase --board imix --arch cortex-m4
popd
echo "done"

echo "Ensuring the submodule for the nRF serialization is checked out"
git submodule update --init --recursive tock-nrf-serialization

echo ""
echo "Now attempting to flash the nRF51."
echo "This requires moving the JTAG."
echo "Move the JTAG connect header to NRF port."
read -n1 -r -p "Press any key to continue..." key
echo ""

pushd tock-nrf-serialization/nrf51822/apps/tock-nrf51822-serialization-sdk11-s130-uart-conn
make imix flash ID=$idcolon
popd
echo "done. Unplug USB from target, plug into debug port."
echo "Check device with tockloader list and tockloader list-attributes."
echo "Check device with Bluetooth sniffer."

