# ClarkeOS Kernel
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

LD = ld
LDFLAGS = -T kernel.ld

KERNEL = kernel
HAL = ../hal/hal.a
OBJECTS = start.o kernel.o memory.o console.o k_printf.o

.PHONY: all clean

.c.o:
	$(CC) $(CFLAGS) -c $<

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<


# Rules

all: $(KERNEL)

kernel: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(HAL)
	@chmod -x $@

clean:
	@rm -f *.o $(KERNEL)

