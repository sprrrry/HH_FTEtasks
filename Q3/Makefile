# Define the microcontroller model and clock frequency
MCU=atmega328p
F_CPU=16000000UL

# Define the compilation flags
CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

# Define the target hex file
TARGET=fibo7seg

all: $(TARGET).hex

$(TARGET).elf: $(TARGET).c
	avr-gcc $(CFLAGS) -o $@ $<

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

clean:
	rm -f *.elf *.hex

.PHONY: all clean

