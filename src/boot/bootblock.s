[BITS 16]       ; We need 16-bit intructions for Real mode
[ORG 0x7c00]    ; The BIOS loads the boot sector into memory location 0x7C00

%define    SYSSEG_REAL      0x1000;     Real mode cs value for System
%define    STACKSEG_REAL    0x0000;     Real mode ss value for Stack
%define    STACKOFF_REAL    0xfff0;     Real mode sp value for Stack
%define    SYSCOSEG_PROT    0x0008;     Protected mode cs value System
%define    SYSDASEG_PROT    0x0010;     Protected mode ds value for System
%define    SYSSTOFF_PROT    0x0009efff; Protected mode sp value for System
%define    SYSCOOFF_PROT    0x00200000; Protected mode offset value for System

boot:
 mov    [bootdrive],dl
 cli
 xor    word    ax, ax
 mov    word    ds, ax
 mov    word    es, ax
 mov    word    ax, STACKSEG_REAL
 mov    word    ss, ax
 mov    word    sp, STACKOFF_REAL
 jmp    0:next
next:
 call   dispostext
 call   loadsetup
 lgdt   [gdt_desc]
 call   remap8259
 call   getmemorymap
 smsw   ax
 or     ax, 0x0001
 lmsw   ax
 jmp    SYSCOSEG_PROT:prot_launcher      


; This routine uses the BIOS video service routines (still Intel reserved vector, but not remapped
; as we kind of need drivers to get some work done). The 0x13 routine (ah) came out in BIOS'es
; from 1986 but were not in the original BIOS'es. (Which only could display one and one character).
dispostext:
 push   ax
 push   bx
 push   cx
 push   bp
 mov    byte    ah, 0x03
 xor    bh, bh
 int    0x10
 mov    word    cx, 28
 mov    word    bx, 0x0007
 mov    word    bp, ostext
 mov    word    ax, 0x1301
 int    0x10
 pop    bp
 pop    cx
 pop    bx
 pop    ax
 ret

getmemorymap:
 push   ax
 push   bx
 push   es
 push   di
 push   cx
 push   dx
 mov    word    ax, 0x0820
 xor    bx, bx
 pop    dx
 pop    cx
 pop    di
 pop    es
 pop    bx
 pop    ax
 ret



; The loadsetup reads first sector on disk, finds the LBA location for our partition and then reads kernel from sector (LBA+1) 
loadsetup:
 xor    ah,ah
 mov    byte    dl,[bootdrive]
 int    0x13

; Check extension present
 mov    byte    ah, 0x41
 mov    word    bx, 0x55aa
 int    0x13
 test   byte    cl, 0x1

; Read MBR using LBA. 
 mov    word    bp, sp
 push   word    0
 push   word    0
 mov    long    ecx,0
 push   long    ecx
 push   word    0x0000
 push   word    0x9b00
 xor    byte    ah, ah
 mov    byte    al, 0x1
 push   word    ax
 push   word    0x10
 mov    byte    ah, 0x42                               
 mov    byte    dl, [bootdrive]                         
 mov    word    si, sp
 int    0x13
 cmp    byte    ah, 0
 mov    word    sp, bp

;read partition kernel using LBA.
 mov    word    bp, sp
 push   word    0
 push   word    0
 mov    long    ecx,[0x9b00+0x1be+0x8]
 inc    ecx
 push   long    ecx
 push   word    0x1000
 push   word    0x0000
 xor    byte    ah, ah
 mov    byte    al, 0x7f
 push   word    ax
 push   word    0x10
 mov    byte    ah, 0x42
 mov    byte    dl, [bootdrive]
 mov    word    si, sp
 int    0x13
 cmp    byte    ah, 0
 mov    word    sp, bp
 ret

; The IBM BIOS programs the PIC to map IRQ 0x0-0xf to vectors 0x8-0xf which all are
; Intel reserved. Intel has reserved all vectors from 0-31. This routine remaps the
; IRQ 0x0-0xf to vectors 0x20-0x2F which are ok.
remap8259:
 mov    byte    al, 0x11
 out    0x20, al
 dw     0x00eb, 0x00eb
 out    0xa0, al
 dw     0x00eb, 0x00eb
 mov    byte    al, 0x20
 out    0x21, al
 dw     0x00eb, 0x00eb
 mov    byte    al, 0x28
 out    0xa1, al
 dw     0x00eb, 0x00eb
 mov    byte    al, 0x04
 out    0x21, al
 dw     0x00eb, 0x00eb
 mov    byte    al, 0x02
 out    0xa1, al
 dw     0x00eb, 0x00eb
 mov    byte    al, 0x01
 out    0x21, al
 dw     0x00eb, 0x00eb
 out    0xa1, al
 dw     0x00eb, 0x00eb
 mov    byte    al, 0xff
 out    0x21, al
 dw     0x00eb, 0x00eb
 out    0xa1, al
 ret


[BITS 32]   
; This is where we land just after enabling protected mode. So we are now
; in protected mode, copies the system to extended memory and jumps to the system with prot. mode address.                   
prot_launcher:
 mov    long    eax, SYSDASEG_PROT
 mov    word    ds, ax
 mov    word    ss, ax
 mov    word    es, ax
 mov    word    ss, ax
 mov    word    fs, ax
 mov    word    gs, ax
 mov    word    ss, ax
 mov    long    esp, SYSSTOFF_PROT

 cld
 mov    word    es, ax
 mov    long    edi, SYSCOOFF_PROT
 mov    long    esi, 0x00010000
 mov    long    ecx, 0x00001800
 rep 
 movsd

 jmp    SYSCOSEG_PROT:SYSCOOFF_PROT   

bootdrive	db 0

gdt_desc:                       
        dw gdt_end - gdt - 1   
        dd gdt                  

gdt:                   
gdt_null: 
    dd 0
    dd 0
gdt_code:              
    dd 0x0000ffff,0x00cf9a00
gdt_data: 
    dd 0x0000ffff,0x00cf9200
gdt_end:

ostext  db 13,10,'Welcome to bonux 0.0.1',13,10,13,10

times   510-($-$$) db 0
dw  0AA55h
