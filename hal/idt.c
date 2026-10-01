/*==============================================================================
  idt.c -> idt.o
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Interrupt Descriptor Table Procedures
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/


/*==============================================================================
  INCLUDES
==============================================================================*/

#include <kernel/idt.h>

#include <system/system.h>
#include <system/types.h>


/*==============================================================================
  GLOBAL DATA
==============================================================================*/

IDT_descriptor_t IDT[256];		// Interrupt Descriptor Table

struct __attribute__((packed))	// IDT Register structure
{
	uint16_t limit;
	uint32_t base;
} IDTR;


/*==============================================================================
  IDT_install - install the Interrupt Descriptor Table
--------------------------------------------------------------------------------
  Setup the IDTR and set each interrupt to the dummy handler.
==============================================================================*/

void IDT_install()
{
	int i;
	
	IDTR.limit = (sizeof(IDT_descriptor_t) * 256) - 1;
	IDTR.base = (uint32_t)&IDT;
	
	for(i = 0; i < 256; i++)
	{
		set_interrupt_gate(i, dummy_isr, CODE_SEGMENT);
	}
	
	lidt(IDTR);
}


/*==============================================================================
  set_interrupt_gate - setup an interrupt gate
--------------------------------------------------------------------------------
  Set an interrupt gate in the Interrupt Descriptor Table
==============================================================================*/

void set_interrupt_gate(uint8_t interrupt, const void *handler,
                        uint16_t segment_selector)
{
	IDT[interrupt].base_low = (uint32_t)handler & 0xffff;
	IDT[interrupt].segment_selector = segment_selector;
	IDT[interrupt].reserved = 0;
	IDT[interrupt].flags = INTERRUPT_GATE;
	IDT[interrupt].base_high = (uint32_t)handler >> 16;
}

