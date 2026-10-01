;===============================================================================
; pic.s -> pic.o
;-------------------------------------------------------------------------------
; ClarkeOS Kernel - 8259A Programmable Interrupt Controller Procedures
; Copyright (C) 2009 Ryan Clarke
;
; Written by Ryan Clarke
; rfclarke@alum.wpi.edu
;===============================================================================

use32									; Protected mode kernel, i.e. 32-bit
cpu 386									; Target the i386


;===============================================================================
; CONSTANTS
;===============================================================================

; Master PIC Ports
PIC_MASTER_COMMAND equ 0x20
PIC_MASTER_DATA    equ 0x21

; Slave PIC Ports
PIC_SLAVE_COMMAND  equ 0xa0
PIC_SLAVE_DATA     equ 0xa1

; ICW1 Bit Flags
ICW1_ICW4_REQUIRED equ 0x01
ICW1_SINGLE_PIC    equ 0x02
ICW1_BYTE_VECTORS  equ 0x04
ICW1_LEVEL_TRIGGER equ 0x08
ICW1_INIT          equ 0x10

; ICW4 Bit Flags
ICW4_8086_MODE     equ 0x01
ICW4_AUTO_EOI      equ 0x02
ICW4_BUFFER_SLAVE  equ 0x08
ICW4_BUFFER_MASTER equ 0x0C


;===============================================================================
; SYMBOLS
;===============================================================================

global PIC_initialize

global PIC_mask_IRQ
global PIC_unmask_IRQ


;===============================================================================
; CODE SECTION
;===============================================================================

section .text
align 4


;===============================================================================
; PIC_initialize - initialize the two 8259A PICs
;-------------------------------------------------------------------------------
; Initialize the two 8259A PICs in a master/slave configuration.
;===============================================================================

PIC_initialize:	
	cli											; Disable interrupts
	
	mov al, ICW1_INIT | ICW1_ICW4_REQUIRED		; ICW1
	out PIC_MASTER_COMMAND, al
	out PIC_SLAVE_COMMAND, al
	
	mov al, 0x20								; IRQ0-7 offset - int 20h
	out PIC_MASTER_DATA, al
	mov al, 0x28								; IRQ8-15 offset - int 28h
	out PIC_SLAVE_DATA, al
	
	mov al, 0x04								; The slave PIC is connected via
	out PIC_MASTER_DATA, al						; IRQ2, which is bit 2
	mov al, 0x02								; The slave ID is 2 for IRQ2
	out PIC_SLAVE_DATA, al
	
	mov al, ICW4_8086_MODE						; ICW4
	out PIC_MASTER_DATA, al
	out PIC_SLAVE_DATA, al
	
	ret


;===============================================================================
; PIC_mask_IRQ - mask one more more IRQs
;-------------------------------------------------------------------------------
; Mask one or more IRQs via the IMR in the PICs. The PICs see a 1 at a bit
; position as a masked IRQ.
;===============================================================================

PIC_mask_IRQ:
	push ebp
	mov ebp, esp
	
	mov edx, [ebp + 8]						; Move the IRQ mask to EDX
	or dl, dl								; Check if the mask for IRQ0-7 is 0
	jz .slave								; If it is, nothing to change.
	
.master:
	in al, PIC_MASTER_DATA					; Get current IMR from Master PIC
	or al, dl								; Apply the passed IRQ mask
	out PIC_MASTER_DATA, al					; Send the new IMR to the PIC
	
	or dh, dh								; Check if the mask for IRQ8-15 is 0
	jz .end									; If it is, nothing to change.
	
.slave:
	in al, PIC_SLAVE_DATA					; Get the current IMR from Slave PIC
	or al, dh								; Apply the passed IRQ mask
	out PIC_SLAVE_DATA, al					; Send the new IMR to the PIC
	
.end:
	mov esp, ebp
	pop ebp
	
	ret

	
;===============================================================================
; PIC_unmask_IRQ - unmask one more more IRQs
;-------------------------------------------------------------------------------
; Unmask one or more IRQs via the IMR in the PICs. The PICs see a 0 at a bit
; position as a masked IRQ, therefore we must invert the passed mask.
;===============================================================================

PIC_unmask_IRQ:
	push ebp
	mov ebp, esp
	
	mov edx, [ebp + 8]						; Move the IRQ mask to EDX
	or dl, dl								; Check if the mask for IRQ0-7 is 0
	jz .slave								; If it is, nothing to change.

.master:	
	in al, PIC_MASTER_DATA					; Get current IMR for Master PIC
	not dl									; Invert the mask
	and al, dl								; Apply the mask
	out PIC_MASTER_DATA, al					; Send the new IMR to the PIC
	
	or dh, dh								; Check if the mask for IRQ8-15 is 0
	jz .end									; If it is, nothing to change.
	
.slave:
	in al, PIC_SLAVE_DATA					; Get the current IMR for Master PIC
	not dh									; Invert the mask
	and al, dh								; Apply the mask
	out PIC_SLAVE_DATA, al					; Send the new IMR to the PIC
	
.end:
	mov esp, ebp
	pop ebp

	ret

