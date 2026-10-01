# ClarkeOS Hardware Abstraction Layer
# Copyright (C) 2009 Ryan Clarke
#
# Written by Ryan Clarke
# rfclarke@alum.wpi.edu


# Macros

AS = nasm
ASFLAGS = -f elf

CC = gcc
CFLAGS = -Wall -Wextra -ffreestanding -fno-stack-protector -finline-functions -nostdinc -mtune=generic $(INCLUDES) -DBOCHS
INCLUDES = -I../include/

HAL = hal.a
OBJECTS = hal.o idt.o exceptions.o exceptions_asm.o dummy_isr.o pic.o

.PHONY: all clean

.c.o:
	$(CC) $(CFLAGS) -c $<

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<


# Rules

all: $(HAL)

$(HAL): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	@rm -f *.o $(HAL)

