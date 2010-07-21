#include "console.h"
#include "tty.h"

static struct tty_st tty_table[1];

void init_tty()
{
    tty_table[0].constate->position=0;
    tty_table[0].write=write_console;
    tty_table[0].writebuffer.head=0;
    tty_table[0].writebuffer.tail=0;
    tty_table[0].readbuffer.head=0;
    tty_table[0].readbuffer.tail=0;
    tty_write(CONSOLE_PROMPT, CONSOLE_TTY);
    return;
}

void tty_read(char* to, size_t size, const unsigned int tty)
{
    if(tty_table[tty].readbuffer.head==tty_table[tty].readbuffer.tail) {
        *to = NULL;
    } else {
        *to = tty_table[tty].readbuffer.buf[tty_table[tty].readbuffer.head--];
    }

    return;
}

void tty_write(const char* from, const unsigned int tty)
{
    size_t i = 0;
    while(from[i]!=0) {
        tty_pushwrite(from[i++],tty);
    }
    return;
}

void tty_pushwrite(const char code, const unsigned int tty)
{
    PUTCHW(code);
    tty_table[tty].write(tty_table);
    return;
}

void tty_pushread(const char code, const unsigned int tty)
{
    PUTCHR(code);
    return;
}
