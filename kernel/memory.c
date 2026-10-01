/*==============================================================================
  memory.c -> memory.o
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Memory Procedures
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/


/*==============================================================================
  Includes
==============================================================================*/

#include <kernel/console.h>
#include <kernel/memory.h>

#include <system/types.h>


/*==============================================================================
  k_memset - set a memory block to a value
--------------------------------------------------------------------------------
  Fill the first <count> bytes of the memory area pointed to by <dest> with the
  constant byte <value>.
==============================================================================*/

void k_memset(void *dest, uint8_t value, size_t count)
{
	uint8_t *temp = (uint8_t *)dest;
	
	for(; count > 0; count--)
	{
		*temp = value;
		temp++;
	}
}

