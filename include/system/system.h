/*==============================================================================
  assembly.h
--------------------------------------------------------------------------------
  ClarkeOS - System Assembly Procedures Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H


/*==============================================================================
  CONSTANTS
==============================================================================*/

#define CODE_SEGMENT 0x08
#define DATA_SEGMENT 0x10

#define INTERRUPT_GATE 0x8e


/*==============================================================================
  MACROS
==============================================================================*/

#define cli()   asm volatile ("cli")
#define hlt()   asm volatile ("hlt")
#define lgdt(a) asm volatile ("lgdt " # a)
#define lidt(a) asm volatile ("lidt " # a)
#define sti()   asm volatile ("sti")

#ifdef BOCHS
#define bochs_debug() asm volatile ("xchg %bx, %bx")
#endif


#endif /* _ASSEMBLY_H */
