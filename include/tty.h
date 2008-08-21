#ifndef BONUX_TTY_H
#define BONUX_TTY_H

#include "string.h"


#define CONSOLE_TTY 0
#define CONSOLE_SCREEN_MEM_BUF_SIZE 2000
#define CONSOLE_SCREEN_MEM_BUF_START 0x000b8000
#define CONSOLE_SCREEN_MEM_BUF_END 0X000c0000
#define TAB_LENGTH 8

#define TTY_BUF_SIZE 4096

#define PUTCH(c) do {tty_table[0].buffer.head=(++tty_table[0].buffer.head)&(TTY_BUF_SIZE-1); \
                     tty_table[0].buffer.buf[tty_table[0].buffer.head]=(c);} while(0)

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
    struct buf_st buffer;
};

extern void init_tty();
extern void tty_read(char* to, size_t size, const unsigned int tty);
extern void tty_write(const char* from, const unsigned int tty);
extern void tty_push(const char code, const unsigned int tty);

#endif
