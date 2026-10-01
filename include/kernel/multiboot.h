/*==============================================================================
  multiboot.h
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Multiboot Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

#include <system/types.h>


/*==============================================================================
  Macros
==============================================================================*/

/* Multiboot Magic Number */
#define MULTIBOOT_MAGIC 0x2badb002

/* Multiboot Information Flags */
#define MBI_FLAGS_MEM			0x00000001
#define MBI_FLAGS_BOOT_DEVICE	0x00000002
#define MBI_FLAGS_CMDLINE		0x00000004
#define MBI_FLAGS_MOD			0x00000008
#define MBI_FLAGS_AOUT			0x00000010
#define MBI_FLAGS_ELF			0x00000020
#define MBI_FLAGS_MMAP			0x00000040
#define MBI_FLAGS_DRIVES		0x00000080
#define MBI_FLAGS_CONFIG_TABLE	0x00000100
#define MBI_FLAGS_BOOT_LOADER	0x00000200
#define MBI_FLAGS_APM_TABLE		0x00000400
#define MBI_FLAGS_VBE			0x00000800


/*==============================================================================
  Typedefs
==============================================================================*/

/* a.out Symbol Table */
typedef struct __attribute__((packed))
{
  uint32_t tabsize;
  uint32_t strsize;
  uint32_t addr;
  uint32_t reserved;
} aout_symbol_table_t;

/* ELF Section Header Table */
typedef struct __attribute__((packed))
{
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
} elf_section_header_table_t;

/* Multiboot Information Structure */
typedef struct __attribute__((packed))
{
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	
	union
	{
		aout_symbol_table_t aout_sym;
		elf_section_header_table_t elf_sec;
	} syms;
	
	uint32_t mmap_length;
	uint32_t mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	uint32_t boot_loader_name;
	uint32_t apm_table;
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;
} multiboot_info_t;

/* Module Structure */
typedef struct __attribute__((packed))
{
	uint32_t mod_start;
	uint32_t mod_end;
	uint32_t string;
	uint32_t reserved;
} module_t;

/* Memory Map Structure */
typedef struct __attribute__((packed))
{
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
} memory_map_t;

/* Drive Info Structure */
typedef struct __attribute__((packed))
{
	uint32_t size;
	uint8_t drive_number;
	uint8_t drive_mode;
	uint16_t drive_cylinders;
	uint8_t drive_heads;
	uint8_t drive_sectors;
	uint16_t drive_ports;
} drive_info_t;

/* APM Table */
typedef struct __attribute__((packed))
{
	uint16_t version;
	uint16_t cseg;
	uint32_t offset;
	uint16_t cseg_16;
	uint16_t dseg;
	uint16_t cseg_len;
	uint16_t cseg_16_len;
	uint16_t dseg_len;
} apm_table_t;


#endif /* _MULTIBOOT_H */
