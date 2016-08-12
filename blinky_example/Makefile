# Simple makefile that builds all sources in the current directory.
PROJECT = blinky
TOOLCHAIN_PREFIX = arm-none-eabi-

CC          := $(TOOLCHAIN_PREFIX)gcc
CFLAGS      := -mcpu=cortex-m4 -mthumb -g -O0
LD          := $(TOOLCHAIN_PREFIX)ld
LDSCRIPT    := simple.ld
SRC         := $(wildcard *.c)
OBJS        := $(SRC:.c=.o)

.PHONY: all
all: $(PROJECT)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(PROJECT) : $(OBJS)
	$(LD) -T $(LDSCRIPT) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o *.elf $(PROJECT)

