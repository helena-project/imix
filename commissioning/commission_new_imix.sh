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
./ftx_prog --manufacturer MostlyTyped --product "imix IoT Module - TockOS" --new-serial-number $idnocolon > /dev/null
rc=$?;
if [[ $rc != 22 ]]; then
	echo "Error programming FTDI"
	exit 2
fi
echo "done"

echo ""
echo "Finished configuring FTDI."
echo "Unplug USB from the board and connect JTAG to the top of the board."
read -n1 -r -p "Press any key to continue..." key
echo ""

echo "Flashing the bootloader using JTAG..."
tockloader flash imix_bootloader.bin --address 0 --jtag-device ATSAM4LC8C --arch cortex-m4 --board imix --jtag
echo "done"

echo "Setting the id attribute..."
tockloader set-attribute --jtag id $idnocolon
echo "done"

echo "Setting the appaddr attribute..."
tockloader set-attribute --jtag appaddr 0x40000
echo "done"

echo "Ensuring the submodule for Tock is checked out"
git submodule update --init --recursive tock

echo "Flashing the imix kernel"
pushd tock/boards/imix
make flash
popd
echo "done"

echo "Flashing the imix app"
pushd tock/userland/examples/tests/imix
make
tockloader install --jtag --erase
popd
echo "done"

echo "Ensuring the submodule for the nRF serialization is checked out"
git submodule update --init --recursive tock-nrf-serialization

echo ""
echo "Now attempting to flash the nRF51."
echo "This requires moving the JTAG."
echo "Move the tag connect header to the bottom of the board."
read -n1 -r -p "Press any key to continue..." key
echo ""

pushd tock-nrf-serialization/nrf51822/apps/tock-nrf51822-serialization-sdk11-s130-uart-conn
make imix flash ID=$idcolon
popd
echo "done"
