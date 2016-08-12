# imix

## Getting Started

Requirements: 
- JLink programmer 
- ARM embedded toolchain
- openocd
- Exacto knife or other small blade
- Optionally, a large (4.7 uF to 47 uF) capacitor.

The current prototype version has several 'gotchas', and undoubtedly there will be more to come.
Here is the procedure for setting up a new board to be programmed:

1. Cut the RESET line between the FTDI chip and the MCU, as shown here:
![Preview](https://github.com/helena-project/imix/blob/master/cut_reset.png)

2. See https://github.com/helena-project/imix/issues/2 for instructions on how to power the board.

3. Clone this repository. 
4. Attach the JLink to the MCU serial wire debug connector on the board.
4. From the `code` directory, connect to the board with `openocd`:
  ```
  openocd -f connect.cfg
  ```

4. From a separate terminal, keeping `openocd` running in the background, run:
  ```
  telnet localhost 4444
  ```

5. In `telnet`, you will need to run the following commands:
  ```
  reset halt
  flash protect 0 0 10 off
  exit
  ```
  This disables flash write protection, which is originally set when the MCU ships from the factory. Steps 6 and 7 only ever need to be run once, the very first time the board is set up.

6. To build `blinky`, run `make`.

6. To load the `blinky` program and debug it with `gdb`, do the following:
  ```
  arm-none-eabi-gdb -x debug.gdb blinky
  ```

If you let the program run, you should see the user LED blink once per second (toggle twice per second).
