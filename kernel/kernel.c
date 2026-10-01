/*==============================================================================
  kernel.c -> kernel.o
--------------------------------------------------------------------------------
  ClarkeOS Kernel
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/


/*==============================================================================
  INCLUDES
==============================================================================*/

#include <kernel/console.h>
#include <kernel/hal.h>
#include <kernel/kernel.h>
#include <kernel/multiboot.h>

#include <system/system.h>


/*==============================================================================
  k_main - kernel entry point
==============================================================================*/

void k_main(multiboot_info_t *mbi, uint32_t magic)
{
	clear_screen();

	k_printf("Starting ClarkeOS...\n");	
	
	if(magic != MULTIBOOT_MAGIC)
	{
		k_printf("Error: invalid magic number <%#x>\nHalting...", magic);
		return;
	}
	
	HAL_initialize();
	
	k_printf("System Ready.");
	
	while(1){}
}


/*==============================================================================
  print_memory_map - print memory map information provided by the boot loader
==============================================================================*/

void print_memory_map(const multiboot_info_t *mbi)
{
	uint64_t temp;
	memory_map_t *mmap;

	if(mbi->flags & MBI_FLAGS_MMAP)
	{
		k_printf("                  Memory Map\n");
		k_printf("---------------------------------------------\n");
		k_printf("       Start               End           Type\n");
		
		for(mmap = (memory_map_t *)mbi->mmap_addr;
		    (uint32_t)mmap < (mbi->mmap_addr + mbi->mmap_length);
		    mmap = (memory_map_t *)((uint32_t)mmap + mmap->size +
		                            sizeof(mmap->size)))
		{
			temp = mmap->base_addr + mmap->length;
			
			k_printf("0x%x%x-0x%x%x      %u\n",
			         (uint32_t)(mmap->base_addr >> 32),
			         (uint32_t)mmap->base_addr, (uint32_t)(temp >> 32),
			         (uint32_t)temp, mmap->type);
		}
	}
}

