# ClarkeOS
# Copyright (C) 2009 Ryan Clarke
#
# Written by Ryan Clarke
# rfclarke@alum.wpi.edu


# Macros

IMAGEFILE = clarkeos.img
KERNEL = kernel/kernel

.PHONY: all install clean


# Rules

all:
	@cd hal ; $(MAKE)
	@cd kernel ; $(MAKE)

install:
	@mkdir mnt
	@mount $(IMAGEFILE) mnt/ -t ext2 -o loop,offset=32256 && \
	cp --no-preserve=ownership $(KERNEL) mnt/system/ && \
	umount mnt/
	@rmdir mnt

clean:
	@cd hal ; $(MAKE) clean
	@cd kernel ; $(MAKE) clean

