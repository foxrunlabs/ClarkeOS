/*==============================================================================
  kernel.h
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Kernel Procedures Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _KERNEL_H
#define _KERNEL_H

#include <kernel/multiboot.h>
#include <varargs.h>


/*==============================================================================
  Function Prototypes
==============================================================================*/

int k_printf(const char *format, ...);
int k_vsprintf(char *, const char *, va_list);

void print_memory_map(const multiboot_info_t *);


#endif /* _KERNEL_H */
