#ifndef BONUX_TASKS_H
#define BONUX_TASKS_H

#include "asmmacroes.h"

/* The idle task, which is really just the kernel startup routines going into an idle loop after initialization is done, and init starts its life. */
#define ADAMEVA_TASK 0
/* The first real task, which will reside in user mode. */
#define INIT_TASK 1

/* Uhm....Why not ? */
#define MAX_TICKS 10

/* Who on earth will *ever* need more than 50 processes ? */
#define MAX_TASKS 50

#define ZOMBIE 0
#define RUNNING 1

#define FIRST_TSS_IN_GDT 3
#define LOAD_LTR(n) ltr((n<<3) + (FIRST_TSS_IN_GDT<<3))
#define SWITCH_TO_TASK(n) to_task((n<<3) + (FIRST_TSS_IN_GDT<<3))

#define HERTZ 100
#define PITOSCILLATORFREQUENCY 1193180
#define LATCH (PITOSCILLATORFREQUENCY/HERTZ)

extern void register_tss();
extern void init_scheduler();
extern void schedule();
unsigned short copy_current_task(const unsigned long entrypoint);
void insert_running_task(const unsigned short pid);


struct st_gdt {
    unsigned long low;
    unsigned long high;
};
extern struct st_gdt gdt[259];

struct st_tss {
    unsigned long prev;     /* high word reserved */
    unsigned long esp0;
    unsigned long ss0;      /* high word reserved */
    unsigned long esp1;
    unsigned long ss1;      /* high word reserved */
    unsigned long esp2;
    unsigned long ss2;      /* high word reserved */
    unsigned long cr3;
    unsigned long eip;
    unsigned long eflags;
    unsigned long eax;
    unsigned long ecx;
    unsigned long edx;
    unsigned long ebx;
    unsigned long esp;
    unsigned long ebp;
    unsigned long esi;
    unsigned long edi;
    unsigned long es;       /* high word reserved */
    unsigned long cs;       /* high word reserved */
    unsigned long ss;       /* high word reserved */
    unsigned long ds;       /* high word reserved */
    unsigned long fs;       /* high word reserved */
    unsigned long gs;       /* high word reserved */
    unsigned long ldt_ss;   /* high word reserved */
    unsigned long iomap;    /* low word reserved */
};

struct st_pcb {
    unsigned short pid;
    unsigned long ticks;
    struct st_tss tss;
    unsigned short state;
    struct st_pcb* prev;
    unsigned long stack[0x200];
    struct st_pcb* next;
};
extern struct st_pcb tasks[MAX_TASKS];

extern unsigned long ticks;
#endif

