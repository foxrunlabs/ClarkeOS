/*==============================================================================
  varargs.h
--------------------------------------------------------------------------------
  ClarkeOS Kernel - Variable Arguments Header File
  Copyright (C) 2009 Ryan Clarke

  Written by Ryan Clarke
  rfclarke@alum.wpi.edu
==============================================================================*/

#ifndef _VARARGS_H
#define _VARARGS_H


/*==============================================================================
  Type Definitions
==============================================================================*/

typedef __builtin_va_list va_list;


/*==============================================================================
  Macros
==============================================================================*/

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_end(v)		__builtin_va_end(v)
#define va_arg(v,l)		__builtin_va_arg(v,l)


#endif /* _VARARGS_H */
