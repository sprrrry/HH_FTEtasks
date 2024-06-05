# MCU name
MCU = atmega328p

# Source files
MASTER = master
SLAVE = slave

# avr-gcc flags
CFLAGS = -mmcu=$(MCU) -Wall -Os -DF_CPU=16000000UL -std=c99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wl,--gc-sections

# Targets
all: master slave

master: $(MASTER).c
	avr-gcc $(CFLAGS) -o $(MASTER).elf $(MASTER).c
	avr-objcopy -O ihex -R .eeprom $(MASTER).elf $(MASTER).hex

slave: $(SLAVE).c
	avr-gcc $(CFLAGS) -o $(SLAVE).elf $(SLAVE).c
	avr-objcopy -O ihex -R .eeprom $(SLAVE).elf $(SLAVE).hex

clean:
	rm -f *.hex *.elf

.PHONY: all master slave clean

