;===============================================================================
; loader.s -> loader.o
;-------------------------------------------------------------------------------
; ClarkeOS Kernel - Loader Module
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

global start							; Export the loader procedure

extern k_main							; Kernel main function


;===============================================================================
; CONSTANTS
;===============================================================================

PAGEALIGN	equ 0x01					; Page align the OS and modules
MEMINFO 	equ 0x02					; Make memory info available to OS
FLAGS 		equ PAGEALIGN | MEMINFO		; Multiboot flags

MAGIC 		equ 0x1badb002				; Multiboot magic number
CHECKSUM 	equ -(MAGIC + FLAGS)		; Multiboot checksum

STACKSIZE 	equ 0x4000					; 16 KB stack


;===============================================================================
; CODE SECTION
;===============================================================================

section .text
align 4

MultiBootHeader:
	dd MAGIC					; Multiboot magic number
	dd FLAGS					; Multiboot OS flags
	dd CHECKSUM					; Multiboot checksum

start:	
	cli							; Clear interrupts
	lgdt[GDTR]					; Load the new Global Descriptor Table
	
	mov edx, DATA_SEGMENT		; Set the new data segment
	mov ds, edx
	mov es, edx
	mov fs, edx
	mov gs, edx
	mov ss, edx

	jmp CODE_SEGMENT:.continue	; Set the new code segment

.continue:
	mov esp, stack + STACKSIZE	; Set the stack pointer
	
	push eax					; Must be 0x2badb002
	push ebx					; Physical address of Multiboot info structure
	call k_main
	add esp, 8					; Clean the stack

	cli							; Clear interrupts

.hang:
	hlt							; If we return from k_main, hang the computer
	jmp .hang


;===============================================================================
; DATA SECTION
;===============================================================================

section .data
align 4

GDTR:								; Global Descriptor Table Register
	GDT_Limit dw GDT_end-GDT-1		; Compute size of GDT
	GDT_Base  dd GDT				; Base of the GDT

GDT:						; Global Descriptor Table
	NULL_SEG equ $-GDT		; Null Segment Selector (required)
		dd 0
		dd 0
	
	CODE_SEGMENT equ $-GDT	; Code Segment Selector - 4GB Flat Code at 0000h with max 0xfffff limit
		dw 0xffff			; Segment Limit (0-15)
		dw 0				; Segment Base (0-15)
		db 0				; Segment Base (16-23)
		db 10011000b		; Present / Ring 0 / Code / Execute Only
		db 11001111b		; 4KB Granularity / 32-bit / Not available by system software / 0Fh Segment Limit (16-19)
		db 0				; Segment Base (24-31)
	
	DATA_SEGMENT equ $-GDT	; Data Segment Selector - 4GB Flat Data at 0000h with max 0xfffff limit
		dw 0xffff			; Segment Limit (0-15)
		dw 0				; Segment Base (0-15)
		db 0				; Segment Base (16-23)
		db 10010010b		; Present / Ring 0 / Data / Read/Write
		db 11001111b		; 4KB Granularity / 32-bit / Not available by system software / 0Fh Segment Limit (16-19)
		db 0				; Segment Base (24-31)
GDT_end:


;===============================================================================
; BSS SECTION
;===============================================================================

section .bss
align 4

stack:
	resb STACKSIZE

