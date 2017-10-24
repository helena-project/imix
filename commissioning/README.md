Commissioning
=============

This folder contains resources for setting up new imix boards.

Commissioning Overview
----------------------

The commissioning process covers a few things:

1. Set the FTDI device name and serial number.
2. Flashes the boatloader on to the SAM4L.
3. Sets the `board`, `id` and `appaddr` attributes in the flash of the SAM4L.
4. Flashes the `imix` TockOS kernel on the SAM4L.
5. Flashes the "blink" app on the SAM4L.
6. Flashes the serialization code on the nRF51 and programs the ID.

Initial software installation
-----------------------------

To initialize a Hail board:

 * Connect USB to the board
 * Connect a JTAG programmer to the SAM4L
 * Run `./commission_new_imix.sh c098e514xxxx` where the `xxxx` should be
   replaced with a unique device ID
 * Connect a JTAG programmer to the nRF51822
 * Hit `any key` to continue the script

Be sure to label the board with a sticker so that the user knows what the
device's BLE address is.


`ftx_prog`
----------

The `ftx_prog` executable comes from here:
https://github.com/richardeoin/ftx-prog.
It was built for linux amd64, so if the executable doesn't work for you,
you will have to recompile it for your platform.
