[BITS 32]

extern vec_0_handler
extern vec_1_handler
extern vec_2_handler
extern vec_3_handler
extern vec_4_handler
extern vec_5_handler
extern vec_6_handler
extern vec_7_handler
extern vec_8_handler
extern vec_9_handler
extern vec_10_handler
extern vec_11_handler
extern vec_12_handler
extern vec_13_handler
extern vec_14_handler
extern vec_15_handler
extern vec_16_handler
extern vec_17_handler
extern vec_18_handler
extern vec_19_handler
extern vec_20_handler
extern vec_21_handler
extern vec_22_handler
extern vec_23_handler
extern vec_24_handler
extern vec_25_handler
extern vec_26_handler
extern vec_27_handler
extern vec_28_handler
extern vec_29_handler
extern vec_30_handler
extern vec_31_handler 
extern vec_32_handler
extern vec_33_handler
extern vec_128_handler
extern idt

global asm_reginthandlers
global asm_vec_128_handler

asm_reginthandlers:
    push    long    ebx
    push    long    ecx
    push    long    edx
    push    long    edi
    push    long    asm_vec_33_handler
    push    long    asm_vec_32_handler
    push    long    asm_vec_31_handler
    push    long    asm_vec_30_handler
    push    long    asm_vec_29_handler
    push    long    asm_vec_28_handler
    push    long    asm_vec_27_handler
    push    long    asm_vec_26_handler
    push    long    asm_vec_25_handler
    push    long    asm_vec_24_handler
    push    long    asm_vec_23_handler
    push    long    asm_vec_22_handler
    push    long    asm_vec_21_handler
    push    long    asm_vec_20_handler
    push    long    asm_vec_19_handler
    push    long    asm_vec_18_handler
    push    long    asm_vec_17_handler
    push    long    asm_vec_16_handler
    push    long    asm_vec_15_handler
    push    long    asm_vec_14_handler
    push    long    asm_vec_13_handler
    push    long    asm_vec_12_handler
    push    long    asm_vec_11_handler
    push    long    asm_vec_10_handler
    push    long    asm_vec_9_handler
    push    long    asm_vec_8_handler
    push    long    asm_vec_7_handler
    push    long    asm_vec_6_handler
    push    long    asm_vec_5_handler
    push    long    asm_vec_4_handler
    push    long    asm_vec_3_handler
    push    long    asm_vec_2_handler
    push    long    asm_vec_1_handler
    push    long    asm_vec_0_handler
    mov     long    ecx, 34 
    mov     long    edi, idt
refillentries:
    pop     long    edx
    mov     word    bx,dx
    shr     long    edx,16
    mov     word    [edi], bx
    mov     word    [edi+6], dx
    add     long    edi, 8
    dec     long    ecx
    jnz     refillentries
    pop     long    edi
    pop     long    edx
    pop     long    ecx
    pop     long    ebx
ret

align 2
interrupt_return:
    cld
    push    ebx
    push    ecx
    push    edx
    push    edi
    push    esi
    push    ebp
    push    fs
    push    es
    push    ds
    call    eax
    pop     ds
    pop     es
    pop     fs
    pop     ebp
    pop     esi
    pop     edi
    pop     edx
    pop     ecx
    pop     ebx
    mov     byte    al, 0x20
    out     0x20, al
    pop     eax
    add     long    esp,4   ; esp is now at error code location. If we add 4 bytes to stack pointer we are at the right place.
    iret

; "Divide By Zero" Exception (Trap)
asm_vec_0_handler:
    push    long    0
    push    long    eax     
    lea     eax,[vec_0_handler]
    jmp     interrupt_return

; "Debug Exception" Exception (Trap or Fault)
asm_vec_1_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_1_handler]
    jmp     interrupt_return

; "Non Maskable Interrupt" Exception (Trap)
asm_vec_2_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_2_handler]
    jmp     interrupt_return

; "Breakpoint (INT 3)" Exception (Trap)
asm_vec_3_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_3_handler]
    jmp     interrupt_return

; "Overflow" Exception (Trap)
asm_vec_4_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_4_handler]
    jmp     interrupt_return

; "Bound Exception" Exception (Trap)
asm_vec_5_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_5_handler]
    jmp     interrupt_return

; "Invalid Opcode" Exception (Trap)
asm_vec_6_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_6_handler]
    jmp     interrupt_return

; "FPU not available" Exception (Trap)
asm_vec_7_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_7_handler]
    jmp     interrupt_return

; "Double Fault" Exception (Abort)
asm_vec_8_handler:
    push    long    eax
    lea     eax,[vec_8_handler]
    jmp     interrupt_return

; "Coprosessor Segment Overrun" Exception (Abort)
asm_vec_9_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_9_handler]
    jmp     interrupt_return

; "Invalid TSS" Exception (Fault)
asm_vec_10_handler:
    push    long    eax
    lea     eax,[vec_10_handler]
    jmp     interrupt_return

asm_vec_11_handler:
    push    long    eax
    lea     eax, [vec_11_handler]
    jmp     interrupt_return

asm_vec_12_handler:
    push    long    eax
    lea     eax, [vec_12_handler]
    jmp     interrupt_return

asm_vec_13_handler:
    push    long    eax
    lea     eax, [vec_13_handler]
    jmp     interrupt_return

asm_vec_14_handler:
    push    long    eax
    lea     eax, [vec_14_handler]
    jmp     interrupt_return

asm_vec_15_handler:
    push    long    0
    iret;

asm_vec_16_handler:
    push    long    0
    iret;

asm_vec_17_handler:
    iret;

asm_vec_18_handler:
    push    long    0
    iret;

asm_vec_19_handler:
    push    long    0
    iret;

asm_vec_20_handler:
    push    long    0
    iret;

asm_vec_21_handler:
    push    long    0
    iret;

asm_vec_22_handler:
    push    long    0
    iret;

asm_vec_23_handler:
    push    long    0
    iret;

asm_vec_24_handler:
    push    long    0
    iret;

asm_vec_25_handler:
    push    long    0
    iret;

asm_vec_26_handler:
    push    long    0
    iret;

asm_vec_27_handler:
    push    long    0
    iret;

asm_vec_28_handler:
    push    long    0
    iret;

asm_vec_29_handler:
    push    long    0
    iret;

asm_vec_30_handler:
    push    long    0
    iret

asm_vec_31_handler:
    push    long    0
    iret

asm_vec_32_handler:
    push    long    0
    push    long    eax
    mov     byte    al, 0x20        ;Must send EOI, because when a new task is switched in,
    out     0x20, al                ;the interrupt_return will never be reached. What happens if vec_32_handler is slower than the timer interrupt ??
    lea     eax, [vec_32_handler]
    jmp     interrupt_return;

asm_vec_33_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_33_handler]
    jmp     interrupt_return

asm_vec_128_handler:
    push    long    0
    push    long    eax
    lea     eax,[vec_128_handler]
    jmp     interrupt_return
