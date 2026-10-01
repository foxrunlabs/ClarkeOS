;===============================================================================
; exception.s -> exception.o
;-------------------------------------------------------------------------------
; ClarkeOS Kernel - Interrupt Service Routines Procedures Module
; Copyright (C) 2009 Ryan Clarke
;
; Written by Ryan Clarke
; rfclarke@alum.wpi.edu
;===============================================================================

use32									; Protected mode kernel, i.e. 32-bit
cpu 386									; Target the i386


;===============================================================================
; SYMBOLS
;===============================================================================

global exception00
global exception01
global exception02
global exception03
global exception04
global exception05
global exception06
global exception07
global exception08
global exception09
global exception0A
global exception0B
global exception0C
global exception0D
global exception0E
global exception0F
global exception10
global exception11
global exception12
global exception13
global exception14
global exception15
global exception16
global exception17
global exception18
global exception19
global exception1A
global exception1B
global exception1C
global exception1D
global exception1E
global exception1F

extern exception_handler


;===============================================================================
; CODE SECTION
;===============================================================================

section .text
align 4


;===============================================================================
; Exception Interrupt Service Routines
;===============================================================================

exception00:
	push 0						; Dummy error code
	push 0x00					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception01:
	push 0						; Dummy error code
	push 0x01					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception02:
	push 0						; Dummy error code
	push 0x02					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception03:
	push 0						; Dummy error code
	push 0x03					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception04:
	push 0						; Dummy error code
	push 0x04					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception05:
	push 0						; Dummy error code
	push 0x05					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception06:
	push 0						; Dummy error code
	push 0x06					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception07:
	push 0						; Dummy error code
	push 0x07					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception08:
	push 0x08					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception09:
	push 0						; Dummy error code
	push 0x09					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception0A:
	push 0x0a					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub
	

exception0B:
	push 0x0b					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception0C:
	push 0x0c					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception0D:
	push 0x0d					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception0E:
	push 0x0e					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception0F:
	push 0						; Dummy error code
	push 0x0f					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception10:
	push 0						; Dummy error code
	push 0x10					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception11:
	push 0x11					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception12:
	push 0						; Dummy error code
	push 0x12					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception13:
	push 0						; Dummy error code
	push 0x13					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception14:
	push 0						; Dummy error code
	push 0x14					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception15:
	push 0						; Dummy error code
	push 0x15					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception16:
	push 0						; Dummy error code
	push 0x16					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception17:
	push 0						; Dummy error code
	push 0x17					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception18:
	push 0						; Dummy error code
	push 0x18					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception19:
	push 0						; Dummy error code
	push 0x19					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception1A:
	push 0						; Dummy error code
	push 0x1A					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception1B:
	push 0						; Dummy error code
	push 0x1B					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception1C:
	push 0						; Dummy error code
	push 0x1C					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception1D:
	push 0						; Dummy error code
	push 0x1D					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception1E:
	push 0						; Dummy error code
	push 0x1E					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


exception1F:
	push 0						; Dummy error code
	push 0x1F					; Exception number
	push exception_handler		; Exception handler
	
	jmp exception_stub


;===============================================================================
; exception_stub
;-------------------------------------------------------------------------------
; A general stub for all exceptions. This stub is jumped to from
; an interrupt handler and expects an error code and a pointer to the C level
; exception handling routine. This stub will set the data segment registers to
; the global data segment and will push the original ESP to the stack as an
; argument to the C level exception handling routine.
;===============================================================================

exception_stub:
	pushad					; Save everything
	push ds
	push es
	push fs
	push gs
		
	mov ebp, esp
	; Frame: gs, fs (+4), es (+8), ds (+12), edi (+16), esi (+20), ebp (24),
	;        esp (+28), ebx (+32), edx (+36), ecx (+40), eax (+44),
	;        handler (+48), int_no (+52), error (+54), eip (+60), cs (+64),
	;        eflags (+68)
	lea eax, [ebp + 72]		; Computer the original ESP value
	push eax				; Original ESP
	push dword [ebp + 52]	; Exception number
	call [ebp + 48]			; Pointer to C level exception handler
	add esp, 8				; Clean the stack
	
	pop gs
	pop fs
	pop es
	pop ds
	popad
	
	add esp, 12				; Clean the stack of the error number, exception
							; number, and exception handler		
	iretd

