/*==============================================================================
  hal.c -> hal.o
--------------------------------------------------------------------------------
  ClarkeOS Hardware Abstraction Layer
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/


/*==============================================================================
  Includes
==============================================================================*/

#include <kernel/exceptions.h>
#include <kernel/hal.h>
#include <kernel/idt.h>
#include <kernel/pic.h>


/*==============================================================================
  Static Functions
==============================================================================*/

static void CPU_initialize();


/*==============================================================================
  HAL_initialize - initalize the hardware abstraction layer
==============================================================================*/

void HAL_initialize()
{
	CPU_initialize();
	
	PIC_initialize();
	PIC_mask_IRQ(IRQ_ALL);
	
	enable_interrupts();
}

static void CPU_initialize()
{
	IDT_install();
	install_exceptions();
}

