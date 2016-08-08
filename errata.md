Errata for v1.0 prototypes
==========================

1. Power LEDs don't come on
---------------------------

Cause:

This issue is due to a lack of bypass capacitance on the output of the bq24230 (the battery charger and power path IC).
Without a high capacitance on the output, the IC is unstable and does not produce a regulated output voltage.


Workarounds:

The general principle is to add a suitable bypass capacitor to the output of the bq24230 (U1).
There are several ways to achieve this:

1. Plug in the device. With the board face up and oriented like a capital 'T', touch 
the leads of a large (4.7uF to 47uF) capacitor from GND to the upper pad of either R19 or R20.
The LEDS should immediately turn on, and the 3.3V power rail should be working. 
Note that because the capacitor is not permanently attached, the power supply may 
occasionally become unstable again, and the process must be repeated.

2. (recommended) Remove R18 and R19. With the board face up and oriented like a capital 'T', 
solder a large (4.7uF to 47uF) capacitor from the rightmost pad of R18 to the upper pad of R19.
An 0603 capacitor is ideal if possible, since it happens to be the perfect dimensions to bridge the gap.

3. (untested) If no suitable capacitor is on hand, it should be possible to directly apply an input 
voltage that bypasses the power path IC. Solder a wire to the upper pad of R19 (R19 can be removed if desired).
The input voltage at this point should be between 3.4 V and 5.5 V. The chances of this method succeeding are
higher if the bq24230 (U1) is removed, and a 0.1uF to 1uF bypass capacitor is applied on the input rail.


2. MCU Reset line is permanently low
---------------------------------

Cause: D8 is incorrectly connected.

Workaround: Remove D8. The reset line should then be at 3.3V by default, or ground when the reset button is pressed.


3. Tag Connect programmer cannot drive the reset line
-----------------------------------------------------

Cause: It is suspected that the solder on the pads of the connector negatively impact the connection enough to
prevent the programmer from sinking enough current to drive the reset line low.

Workaround: Currently unknown.
