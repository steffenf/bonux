[BITS 32]

extern main
global startup32
global idt
global gdt
global os
; This is the startup code for the bonux system. We are now in
; protected mode with interrupts disabled and masked off.
; This routine initializes the segment registers and sets a stack offset in 32-bit linear space
; Then we print an alive message on the screen for debug purposes
; After that we build the idt and registers all interrupts with interrupt_handler which prints
; something to screen. Then sti and unmask keyboard interrupt to see if things work.

section .text
startup32:
 mov    long    eax, 0x00000010
 mov    word    ds, ax
 mov    word    ss, ax
 mov    word    es, ax
 mov    word    ss, ax
 mov    long    esp, 0x0009efff
 mov    word    fs, ax
 mov    word    gs, ax
 call   rebuildgdt
 call   buildidt
 call   enablenminterrupts
 call   main
run:
 jmp    run

rebuildgdt:
 lgdt   [gdt_descriptor]
 ret

buildidt:
 mov    long    edx, interrupt_handler 
 mov    long    eax, 0x00080000
 mov    word    ax, dx
 mov    word    dx, 0x8e00
 mov    long    edi, idt
 mov    long    ecx, 256
fillentries:
 mov    long    [edi],  eax
 mov    long    [edi+4],  edx
 add    edi, 8
 dec    ecx
 jnz    fillentries
 lidt   [idt_descriptor]
 ret

enablenminterrupts:
 mov    byte    al, 00000000b   ;Umask all interrupts...
 out    byte    0x21, al
 in     byte    al, 0x70        ;Enable non maskable interrupts.
 and    al, 01111111b
 out    byte    0x70, al
 ret

interrupt_handler:
 push   long    eax
 push   word    ds
 mov    long    eax, 0x00000010
 mov    word    ds, ax
 pop    word    ds
 mov    byte    al, 0x20
 out    0x20,   al
 pop    long    eax;
 iret

section .data
align 2
idt_descriptor:
 dw    	256*8-1
 dd    	idt

align 8
idt:
 TIMES 	256*8 db 0

align 2
gdt_descriptor:                      
    dw     gdt_end - gdt - 1   
    dd     gdt 

align 8
gdt:                   
gdt_null:              
    dd 0
    dd 0
gdt_code:               
    dd 0x0000ffff,0x00cf9a00
gdt_data:              
    dd 0x0000ffff,0x00cf9200
tss:
TIMES   256*8 db 0
gdt_end: 
