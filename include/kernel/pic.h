/*==============================================================================
  pic.h
--------------------------------------------------------------------------------
  ClarkeOS Kernel - 8259A Programmable Interrupt Controller Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _PIC_H
#define _PIC_H


#define IRQ0    0x0001
#define IRQ1    0x0002
#define IRQ2    0x0004
#define IRQ3    0x0008
#define IRQ4    0x0010
#define IRQ5    0x0020
#define IRQ6    0x0040
#define IRQ7    0x0080
#define IRQ8    0x0100
#define IRQ9    0x0200
#define IRQ10   0x0400
#define IRQ11   0x0800
#define IRQ12   0x1000
#define IRQ13   0x2000
#define IRQ14   0x4000
#define IRQ15   0x8000
#define IRQ_ALL 0xffff


/*==============================================================================
  Function Prototypes
==============================================================================*/

extern void PIC_initialize();

extern void PIC_mask_IRQ(int);
extern void PIC_unmask_IRQ(int);


#endif /* _PIC_H */
