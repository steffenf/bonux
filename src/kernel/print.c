#include "tty.h"
#include "asmmacroes.h"

#include "print.h"

void printk(const char* message)
{
    tty_write(message,CONSOLE_TTY);
}

void dumpcpu()
{
    int i;
    unsigned long reg;

    get_eax(reg);
    printregister("eax", reg);
    get_ebx(reg);
    printregister("ebx", reg);
    get_ecx(reg);
    printregister("ecx", reg);
    get_edx(reg);
    printregister("edx", reg);
    get_esp(reg);
    printregister("esp", reg);
    get_ebp(reg);
    printregister("ebp", reg);
    get_esi(reg);
    printregister("esi", reg);
    get_edi(reg);
    printregister("edi", reg);
    get_cs(reg);
    printregister("cs", reg);
    get_ds(reg);
    printregister("ds", reg);
    get_ss(reg);
    printregister("ss", reg);
    get_es(reg);
    printregister("es", reg);
    get_fs(reg);
    printregister("fs", reg);
    get_gs(reg);
    printregister("gs", reg);
    get_cr3(reg);
    printregister("cr3", reg);
    get_cr0(reg);
    printregister("cr0", reg);
    get_eflags(reg);
    printregister("eflags", reg);
    printk("\n");
}

void printregister(const char* name, const unsigned long value) {
    int i;

    printk(name);
    printk(": ");
    for(i=28;i>=0;i-=4) {
        printnibble(value>>i & 0x0000000f); 
    }
    printk(" ");
}


void printbyte(const unsigned char byte) {
    int i;

    for(i=4;i>=0;i-=4) {
        printnibble(byte>>i & 0x0000000f);
    }
    printk(" ");
 }

void printnibble(const unsigned char nibble)
{
    switch(nibble) {
        case 0: printk("0");break;
        case 1: printk("1");break;
        case 2: printk("2");break;
        case 3: printk("3");break;
        case 4: printk("4");break;
        case 5: printk("5");break;
        case 6: printk("6");break;
        case 7: printk("7");break;
        case 8: printk("8");break;
        case 9: printk("9");break;
        case 10: printk("A");break;
        case 11: printk("B");break;
        case 12: printk("C");break;
        case 13: printk("D");break;
        case 14: printk("E");break;
        case 15: printk("F");break;
        default: printk("?");break;
    }
}

