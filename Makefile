.SUFFIXES:
.SUFFIXES: .c .o
SHELL = /bin/sh

MCU ?= attiny13
PORT ?= /dev/ttyACM0
PROGRAMMER ?= stk500v2
BITCLOCK ?= 50
FUSES ?= -U lfuse:w:0x69:m -U hfuse:w:0xFF:m # 4.8 MHz

CFLAGS += -gdwarf-2 -Ofast -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Werror -Wextra -pedantic -maccumulate-args -mcall-prologues -mint8 -mrelax
LDFLAGS += -gdwarf-2
LDLIBS += -lm

BIN = main
SRC = main.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: $(BIN).elf

$(BIN).elf: $(OBJ)
	avr-gcc -mmcu=$(MCU) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)
	avr-size --mcu=$(MCU) -C $@

%.o: %.c
	avr-gcc -c -mmcu=$(MCU) $(CFLAGS) $< -o $@

flash: all
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature -j .text -j .data $(BIN).elf $(BIN).hex
	avrdude -p $(MCU) -P $(PORT) -c $(PROGRAMMER) -U flash:w:$(BIN).hex -B $(BITCLOCK)

.PHONY: fuses
fuses: 
	avrdude -p $(MCU) -P $(PORT) -c $(PROGRAMMER) $(FUSES)

clean:
	$(RM) $(OBJ) $(DEP) $(patsubst %,$(BIN).%, elf hex)
