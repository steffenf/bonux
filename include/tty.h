#ifndef BONUX_TTY_H
#define BONUX_TTY_H

#include "string.h"


#define CONSOLE_TTY 0
#define CONSOLE_SCREEN_MEM_BUF_SIZE 2000
#define CONSOLE_SCREEN_MEM_BUF_START 0x000b8000
#define CONSOLE_SCREEN_MEM_BUF_END 0X000c0000
#define TAB_LENGTH 8

#define TTY_BUF_SIZE 2048

#define PUTCHW(c) do {tty_table[0].writebuffer.head=(++tty_table[0].writebuffer.head)&(TTY_BUF_SIZE-1); \
                     tty_table[0].writebuffer.buf[tty_table[0].writebuffer.head]=(c);} while(0)

#define PUTCHR(c) do {tty_table[0].readbuffer.head=(++tty_table[0].readbuffer.head)&(TTY_BUF_SIZE-1); \
                     tty_table[0].readbuffer.buf[tty_table[0].readbuffer.head]=(c);} while(0)

struct buf_st {
    unsigned char buf[TTY_BUF_SIZE];
    unsigned short int head;
    unsigned short int tail;
};

struct con_state_st {
    unsigned char screen[CONSOLE_SCREEN_MEM_BUF_SIZE];
    unsigned short int position;
};

struct tty_st {
    void (*write)(const struct tty_st* tty); 
    struct con_state_st* constate;
    struct buf_st writebuffer;
    struct buf_st readbuffer;
};

extern void init_tty();
extern void tty_read(char* to, size_t size, const unsigned int tty);
extern void tty_write(const char* from, const unsigned int tty);
extern void tty_pushwrite(const char code, const unsigned int tty);

#endif
