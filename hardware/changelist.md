v1.3:

* Removed ground plane near RF233 antenna
* Analog switch added as isolator for RF233 SPI and sense/NRF I2C
* Resistor added between FTDI_DTR and !RESET
* Battery charger configured for 500mA operation
* VHIGHSAMPLE from TRNG routed to ADCIFE6
* Reassigned A0-5 from ADCIFE1-6 to ADCIFE0-5
* GPIO8 reassigned to PA20
* LIGHT_INT reassigned to PC25
* Added KERNEL LED
* Overhaul of imix.lbr (documentation layers)
* Used P/N M20-9980545 for J4

v2.1:

* Form factor: now a 2.5"X4" rectangle
* Removed battery circuit
* FTDI chip powered correctly for low power
* Removed unnecessary resistors
* Renumbered some resistors and capacitors
* Changed pull-ups to 10K from 4.7K
* Removed unnecessary battery charger IC
* Removed all power gates except TRNG
* Removed header 1 and reassigned pins to the other headers
* Shunts instead of cutting traces
* Rearranged pinout on headers to simplify layout
* JST battery connector instead of battery clips
* Minor pinout changes on the MCU
* Cheaper diodes for power input
* Nicer more clicky buttons
* Power LEDs on the USB and nowhere else
* Trace width increased to 8 mil
* SPI header removed
* Debug USB moved to opposite side of board
* Mounting holes in a 2"X3.75" rectangle
* Extra SPI header removed
* Populate the sense resistors for TRNG
* Nicer silkscreen with TockOS and Imix urls
