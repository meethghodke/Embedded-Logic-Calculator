################################################################################
# Makefile for MyAVR Programm                                                  #

PORT=COM3
PROGRAMMER=avr911
TARGET_CPU=atmega88pa
TARGET_PROCESSOR=m88p
CFLAGS=-Wall -Os -c -mmcu=$(TARGET_CPU)
LDFLAGS=-mmcu=$(TARGET_CPU)


# Program ######################################################################
all: main.hex

program: main.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:main.hex:i

# Hex File #####################################################################
main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o lcd.o i2c_master.o init.o
	avr-gcc $(LDFLAGS) main.o lcd.o i2c_master.o init.o -o main.elf


# Object Files #################################################################
lcd.o: lcd.c
	avr-gcc $(CFLAGS) lcd.c -o lcd.o

i2c_master.o: i2c_master.c
	avr-gcc $(CFLAGS) i2c_master.c -o i2c_master.o

main.o: main.c
	avr-gcc $(CFLAGS) main.c -o main.o

init.o: init.c init.h
	avr-gcc -mmcu=atmega88pa -c -Os init.c



# Clean ########################################################################
clean:
	rm -f *.o *.elf *.hex *~
