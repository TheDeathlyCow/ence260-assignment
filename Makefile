# File:   Makefile
# Author: Michael Alpenfels
# Date:   17 October 2021
# Descr:  Makefile for ENCE260 assignment 2 (2021).

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.


game.o: game.c ../../drivers/avr/system.h ../../drivers/button.h game_controller.h position.h maze.h levels.h
	$(CC) -c $(CFLAGS) $< -o $@

game_controller.o: game_controller.c game_controller.h maze.h input.h levels.h position.h move.h menus.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/led.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

position.o: position.c ../../drivers/avr/pio.c ../../drivers/avr/pio.h position.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

levels.o: levels.c levels.h maze.h bitmap.h position.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

bitmap.o: bitmap.c ../../drivers/avr/pio.c ../../drivers/avr/pio.h bitmap.h position.h
	$(CC) -c $(CFLAGS) $< -o $@

maze.o: maze.c bitmap.h maze.h position.h
	$(CC) -c $(CFLAGS) $< -o $@

move.o: move.c move.h maze.h position.h input.h
	$(CC) -c $(CFLAGS) $< -o $@

input.o: input.c input.h ../../drivers/navswitch.h ../../drivers/button.h position.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/display.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../utils/tinygl.h ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

menus.o: menus.c menus.h ../../drivers/led.h ../../drivers/button.h ../../utils/tinygl.h ../../fonts/font5x7_1.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

game_controller.o: game_controller.c game_controller.h maze.h position.h input.h levels.h move.h menus.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
game.out: game.o pio.o system.o bitmap.o timer.o pacer.o maze.o position.o move.o input.o navswitch.o game_controller.o button.o levels.o led.o menus.o display.o tinygl.o ledmat.o font.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


