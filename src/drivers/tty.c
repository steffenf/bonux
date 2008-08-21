#include "console.h"
#include "tty.h"

static struct tty_st tty_table[1];

void init_tty()
{
    tty_table[0].constate->position=0;
    tty_table[0].write=write_console;
    tty_table[0].buffer.head=0;
    tty_table[0].buffer.tail=0;
    tty_write(CONSOLE_PROMPT, CONSOLE_TTY);
    return;
}

void tty_read(char* to, size_t size, const unsigned int tty)
{
    return;
}

void tty_write(const char* from, const unsigned int tty)
{
    size_t i = 0;
    while(from[i]!=0) {
        tty_push(from[i++],tty);
    }
    return;
}

void tty_push(const char code, const unsigned int tty)
{
    PUTCH(code);
    tty_table[tty].write(tty_table);
    return;
}
