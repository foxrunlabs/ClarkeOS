/*==============================================================================
  exceptions.c -> exceptions.o
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Intel Exceptions Procedures
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/


/*==============================================================================
  INCLUDES
==============================================================================*/

#include <kernel/console.h>
#include <kernel/exceptions.h>
#include <kernel/idt.h>
#include <kernel/kernel.h>

#include <system/system.h>
#include <system/types.h>


/*==============================================================================
  GLOBAL DATA
==============================================================================*/

char *exception_names[] = { "Divide Error",
                            "Reserved",
                            "Non-maskable Interrupt",
                            "Breakpoint",
                            "Overflow",
                            "BOUND Range Exceeded",
                            "Invalid Opcode",
                            "No Math Coprocessor",
                            "Double Fault",
                            "Coprocessor Segment Overrun",
                            "Invalid TSS",
                            "Segment Not Present",
                            "Stack-Segment Fault",
                            "General Protection Fault",
                            "Page Fault",
                            "Reserved",
                            "Math Fault",
                            "Alignment Check",
                            "Machine Check",
                            "SIMD Floating-Point Exception",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved",
                            "Reserved", 
                            "Reserved" };


/*==============================================================================
  install_exceptions - install the exception handlers for interrupts 0x00-0x1f
--------------------------------------------------------------------------------
==============================================================================*/

void install_exceptions()
{
	set_interrupt_gate(0x00, exception00, CODE_SEGMENT);
	set_interrupt_gate(0x01, exception01, CODE_SEGMENT);
	set_interrupt_gate(0x02, exception02, CODE_SEGMENT);
	set_interrupt_gate(0x03, exception03, CODE_SEGMENT);
	set_interrupt_gate(0x04, exception04, CODE_SEGMENT);
	set_interrupt_gate(0x05, exception05, CODE_SEGMENT);
	set_interrupt_gate(0x06, exception06, CODE_SEGMENT);
	set_interrupt_gate(0x07, exception07, CODE_SEGMENT);
	set_interrupt_gate(0x08, exception08, CODE_SEGMENT);
	set_interrupt_gate(0x09, exception09, CODE_SEGMENT);
	set_interrupt_gate(0x0a, exception0A, CODE_SEGMENT);
	set_interrupt_gate(0x0b, exception0B, CODE_SEGMENT);
	set_interrupt_gate(0x0c, exception0C, CODE_SEGMENT);
	set_interrupt_gate(0x0d, exception0D, CODE_SEGMENT);
	set_interrupt_gate(0x0e, exception0E, CODE_SEGMENT);
	set_interrupt_gate(0x0f, exception0F, CODE_SEGMENT);
	set_interrupt_gate(0x10, exception10, CODE_SEGMENT);
	set_interrupt_gate(0x11, exception11, CODE_SEGMENT);
	set_interrupt_gate(0x12, exception12, CODE_SEGMENT);
	set_interrupt_gate(0x13, exception13, CODE_SEGMENT);
	set_interrupt_gate(0x14, exception14, CODE_SEGMENT);
	set_interrupt_gate(0x15, exception15, CODE_SEGMENT);
	set_interrupt_gate(0x16, exception16, CODE_SEGMENT);
	set_interrupt_gate(0x17, exception17, CODE_SEGMENT);
	set_interrupt_gate(0x18, exception18, CODE_SEGMENT);
	set_interrupt_gate(0x19, exception19, CODE_SEGMENT);
	set_interrupt_gate(0x1a, exception1A, CODE_SEGMENT);
	set_interrupt_gate(0x1b, exception1B, CODE_SEGMENT);
	set_interrupt_gate(0x1c, exception1C, CODE_SEGMENT);
	set_interrupt_gate(0x1d, exception1D, CODE_SEGMENT);
	set_interrupt_gate(0x1e, exception1E, CODE_SEGMENT);
	set_interrupt_gate(0x1f, exception1F, CODE_SEGMENT);
}


/*==============================================================================
  exception_handler - generic exception handler
--------------------------------------------------------------------------------
  Exception handler for interrupts 0x00 - 0x1F. The errors will print the error
  code. A stack trace is printed at the end for debugging purposes.
  
  Stack: error (-4), eip (-3), cs (-2), eflags (-1)
==============================================================================*/

void exception_handler(int interrupt, const uint32_t *esp)
{
	set_text_attribute(BRIGHT_WHITE, RED);
	clear_screen();
	
	if(interrupt == 0x08 || (interrupt >= 0x0a && interrupt <= 0x0e) || interrupt == 0x11)
	{
		k_printf("%s - Error Code: %#x\n\n", exception_names[interrupt], *(esp - 4));
	}
	else
	{
		k_printf("%s\n\n", exception_names[interrupt]);
	}
	
	print_stack_trace(esp);
	
	hlt();
}


/*==============================================================================
  print_stack_trace - print a stack trace
--------------------------------------------------------------------------------
  Print a stack trace, to include the EIP, EFLAGS, and ESP.
  
  Stack: error (-4), eip (-3), cs (-2), eflags (-1)
==============================================================================*/

void print_stack_trace(const uint32_t *stack)
{
	int i;
	
	k_printf("EIP:\t%#x\nEFLAGS:\t%#x\nESP:\t%#x\n\n", *(stack - 3),
	         *(stack - 1), stack);	
	
	for(i = 0; i < 16; i++)
	{
		k_printf("STACK\t[%#x]\t%x\n", stack, *stack);
		stack++;
	}
}

