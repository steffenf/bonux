/* 
 * The startup32 assembly code calls this entrypoint. From now on we can do it
 * all in "high" level c with some portions of inline assembly.
 * Right now we just make something happen to the text mode vga screen to see that
 * we actually are in c....
 */

#include "keyboard.h"
#include "tty.h"
#include "console.h"
#include "hi_interrupthandlers.h"
#include "asmmacroes.h"
#include "tasks.h"
#include "time.h"
#include "main.h"
#include "mem.h"
#include "time.h"

static void getsysteminfo();
static void init_task();
static void login_task();

struct sys_inf_st sysinf;

/* Maskable interrupts were disabled in bootblock.s */
int main(void)
{
    init_keyboard();
    init_console();
    init_tty();
    init_paging();
    init_scheduler();
    register_tss();
    init_unix_time();
    register_interrupthandlers();
    insert_running_task(copy_current_task((unsigned long)init_task));
    sti();

    for(;;) {
        printk("kernel process");
        dumpcpu();
        chill(4000);
    }

    return 0;
}

static void init_task() 
{
    char key;

    for(;;) {
        tty_read(&key,1,0);
        if(key=='l') {
            insert_running_task(copy_current_task((unsigned long)login_task));
        }
        chill(4000);
    }
}

static void login_task() 
{
    printk("login as: ");
    for(;;);
}

static void getsysteminfo()
{
    getmemsize(sysinf.totmem);
}

