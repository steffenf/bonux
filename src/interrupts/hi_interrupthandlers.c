#include "keyboard.h"
#include "tasks.h"
#include "panic.h"
#include "hi_interrupthandlers.h"

extern asm_reginthandlers();
extern asm_vec_128_handler();


static void insert_interrupthandler(const unsigned short vector, const unsigned long address);

void register_interrupthandlers()
{
    asm_reginthandlers();
    insert_interrupthandler(128, (unsigned long)asm_vec_128_handler);
}

/* This stuff inserts a new interrupthandler for the specified vector */
static void insert_interrupthandler(const unsigned short vector, const unsigned long address)
{
    idt[vector].low=0x00080000;
    idt[vector].low|=(address&0x0000ffff);
    idt[vector].high=(address&0xffff0000);
    idt[vector].high|=0x00008e00;
}

void vec_0_handler()
{
    panic("Division by zero");
}

void vec_1_handler()
{
    panic("Debug exception");
   
}

void vec_2_handler()
{
    panic("Non maskable interrupt");
}

void vec_3_handler()
{
    panic("Breakpoint");
}

void vec_4_handler()
{
    panic("Overflow");
}

void vec_5_handler()
{
    panic("Bound");
}

void vec_6_handler()
{
    panic("Invalid opcode");
}

void vec_7_handler()
{
    panic("FPU not available");
}

void vec_8_handler()
{
    panic("Double fault");
}

void vec_9_handler()
{
    panic("Coprocessor segment overrun");
}

void vec_10_handler()
{
    panic("Invalid TSS");
}

void vec_11_handler()
{
    panic("Segment not present");
}

void vec_12_handler()
{
    panic("Stack segment fault");
}

void vec_13_handler()
{
    panic("General protection fault");
}

void vec_14_handler()
{
    panic("Page fault");
}

void vec_15_handler()
{
}

void vec_16_handler()
{
}

void vec_17_handler()
{
}

void vec_18_handler()
{
}

void vec_19_handler()
{
}

void vec_20_handler()
{
}

void vec_21_handler()
{
}

void vec_22_handler()
{
}

void vec_23_handler()
{
}

void vec_24_handler()
{
}

void vec_25_handler()
{
}

void vec_26_handler()
{
}

void vec_27_handler()
{
}

void vec_28_handler()
{
}

void vec_29_handler()
{
}

void vec_30_handler()
{
}

void vec_31_handler()
{
}

void vec_32_handler()
{
    schedule();
}

void vec_33_handler()
{
    read_keyboard();
}

void vec_128_handler()
{
    panic("System call not yet implemented");
}
