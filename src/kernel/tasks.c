#include "stddef.h"
#include "tasks.h"
#include "print.h"
#include "time.h"
#include "mem.h"

struct st_pcb tasks[MAX_TASKS]; 
static struct st_pcb* current;
unsigned long ticks;

static void remove_running_task(const unsigned short pid);
static unsigned short get_free_pid();

/* This function sets up the scheduler with the ADAMEVA task. */
void init_scheduler() {
    int i=0;

    for(;i<MAX_TASKS;i++) {
        tasks[i].pid=i;
        tasks[i].ticks=MAX_TICKS;
        tasks[i].state = ZOMBIE;
        tasks[i].next = NULL;
        tasks[i].prev =  NULL;
    }

    tasks[ADAMEVA_TASK].next    =   &tasks[ADAMEVA_TASK];
    tasks[ADAMEVA_TASK].prev    =   &tasks[ADAMEVA_TASK];
    tasks[ADAMEVA_TASK].state   =   RUNNING;
    current                     =   &tasks[ADAMEVA_TASK];

    /* This control register must be set in the tss, because the processor never stores cr3 to tss when switching out a task. It only reads the tss.cr3 when switching in a task. */
    get_cr3(current->tss.cr3);

    /* Set Programmable Interrupt Timer to 100Hz */
    outbyte(0x43,0x34);
    outbyte(0x40,LATCH&0xff);
    outbyte(0x40,(LATCH>>8));
}

void schedule() {
    ticks++;
    update_unix_time();
    if(--current->ticks==0) {
        current->ticks=MAX_TICKS;
        current=current->next;
        SWITCH_TO_TASK(current->pid);
    }
}

void register_tss() {
    /* Now create 256 TSS segment descriptors in GDT starting at position 3 in GDT (0=0,1=CS,2=DS) */
    /* We can now use gdt[259] which hooks up to the gdt structure in setup32.s */

    unsigned short i=0;
    
    for(;i<MAX_TASKS;i++) {
        gdt[i+3].low=((unsigned long)(&tasks[i].tss))<<16;                  //Bits 0-15 of tss address
        gdt[i+3].low+=0xffff;                                               //Bits 0-15 of segment limit.
        gdt[i+3].high=((unsigned long)(&tasks[i].tss))&0xff000000;          //Bits 24-31 of tss address.
        gdt[i+3].high+=0x8f8900;                                            //12 bits with flags, the "1111" is bits 16-19 of segment limit: 1000 1111 1000 1001
                                                                            //"Not busy", "DPL 0", "Present", "AVL=0", "Granularity=1"   
        gdt[i+3].high+=(((unsigned long)(&tasks[i].tss))&0x00ff0000)>>16;   //Bits 16-23 of tss address
    }

    /* Load task register with tss located at gdt[3]. The processor must initally be chosen to run a task */
    LOAD_LTR(ADAMEVA_TASK);
}

/* This is for setting up new task. Everything is copied except for esp (own stack) and cr3 (own page directory) */
unsigned short copy_current_task(const unsigned long entrypoint) {
    unsigned short pid = get_free_pid();
    
    tasks[pid].pid=pid;
    tasks[pid].ticks=MAX_TICKS;
    tasks[pid].state=ZOMBIE;
    tasks[pid].next=NULL;
    tasks[pid].prev=NULL;

    tasks[pid].tss.prev=(unsigned long)NULL;
    tasks[pid].tss.esp0=((unsigned long)(&tasks[pid].next));
    get_ss(tasks[pid].tss.ss0);
    get_esp(tasks[pid].tss.esp1);
    get_ss(tasks[pid].tss.ss1);
    get_esp(tasks[pid].tss.esp2);
    get_ss(tasks[pid].tss.ss2);
    tasks[pid].tss.cr3=(unsigned long)(pde[pid]);
    tasks[pid].tss.eip=entrypoint;
    get_eflags(tasks[pid].tss.eflags);
    get_eax(tasks[pid].tss.eax)
    get_ecx(tasks[pid].tss.ecx);
    get_edx(tasks[pid].tss.edx);
    get_ebx(tasks[pid].tss.ebx);
    tasks[pid].tss.esp=((unsigned long)(&(tasks[pid].next)));
    get_ebp(tasks[pid].tss.ebp);
    get_esi(tasks[pid].tss.esi);
    get_edi(tasks[pid].tss.edi);
    get_es(tasks[pid].tss.es);
    get_cs(tasks[pid].tss.cs);
    get_ss(tasks[pid].tss.ss);
    get_ds(tasks[pid].tss.ds);
    get_fs(tasks[pid].tss.fs);
    get_gs(tasks[pid].tss.gs);
    tasks[pid].tss.ldt_ss=0;    /* Uhhmm...Don't use LDT's right now. Set it to 0 for the moment should be ok */
    tasks[pid].tss.iomap=0;     /* Uhmmm...Let's do this when we go luser mode.*/
    
    return pid;
}

static void remove_running_task(const unsigned short pid) {
    tasks[pid].prev->next=tasks[pid].next;
    tasks[pid].next->prev=tasks[pid].prev;
    tasks[pid].state=ZOMBIE;
}

void insert_running_task(const unsigned short pid) {
    current->prev->next=&tasks[pid];
    tasks[pid].prev=current->prev;
    tasks[pid].next=current;
    current->prev=&tasks[pid];
    tasks[pid].state=RUNNING;
}

static unsigned short get_free_pid() {
    unsigned short i=0;

    for(i=0;i<MAX_TASKS;i++) {
        if(tasks[i].state==ZOMBIE) {
            return i;
        }
    }
    panic("Process table full...");
}


