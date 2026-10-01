/*==============================================================================
  idt.h
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Interrupt Descriptor Table Procedures Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _IDT_H
#define _IDT_H

#include <system/types.h>


/*==============================================================================
  Type Definitions
==============================================================================*/

// Interrupt Descriptor Table descriptor
typedef struct __attribute__((packed))
{
	uint16_t base_low;
	uint16_t segment_selector;
	uint8_t  reserved;
	uint8_t  flags;
	uint16_t base_high;
} IDT_descriptor_t;


/*==============================================================================
  Function Prototypes
==============================================================================*/

void IDT_install();
void set_interrupt_gate(uint8_t, const void *, uint16_t);

extern void dummy_isr();


#endif /* _IDT_H */
