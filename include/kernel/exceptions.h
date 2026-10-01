/*==============================================================================
  interrupts.h
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Intel Exceptions Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <system/types.h>


/*==============================================================================
  Function Prototypes
==============================================================================*/

void install_exceptions();
void exception_handler(int, const uint32_t *);
void print_stack_trace(const uint32_t *);

// Located in exception.s
extern void exception00();
extern void exception01();
extern void exception02();
extern void exception03();
extern void exception04();
extern void exception05();
extern void exception06();
extern void exception07();
extern void exception08();
extern void exception09();
extern void exception0A();
extern void exception0B();
extern void exception0C();
extern void exception0D();
extern void exception0E();
extern void exception0F();
extern void exception10();
extern void exception11();
extern void exception12();
extern void exception13();
extern void exception14();
extern void exception15();
extern void exception16();
extern void exception17();
extern void exception18();
extern void exception19();
extern void exception1A();
extern void exception1B();
extern void exception1C();
extern void exception1D();
extern void exception1E();
extern void exception1F();


#endif /* _EXCEPTIONS_H */
