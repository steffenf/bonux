#include "asmmacroes.h"

#include "console.h"

static void clear_screen();
static void update_cursor();

static unsigned short int currpos=0;
static unsigned char* vgamem=(unsigned char*)CONSOLE_SCREEN_MEM_BUF_START;

void init_console() 
{
    clear_screen();
    update_cursor();
        
}

void write_console(const struct tty_st* tty)
{
    switch(tty->writebuffer.buf[tty->writebuffer.head]) {
        case '\r':
            currpos+=((COLUMNS<<1)-(currpos%(COLUMNS<<1)));
            break;
        case '\n':
            currpos+=((COLUMNS<<1)-(currpos%(COLUMNS<<1)));
            break;
        case '\t':
            currpos+=(TAB_LENGTH<<1);
            break;
        default:
            vgamem[currpos]=tty->writebuffer.buf[tty->writebuffer.head];
            currpos+=2;
            break;
    }

    if(currpos>=LINES*COLUMNS*2) {
        clear_screen();
    }

    update_cursor();
}


static void clear_screen()
{
    unsigned int i;
  
    for(i=0;i<(CONSOLE_SCREEN_MEM_BUF_END-CONSOLE_SCREEN_MEM_BUF_START);i+=2) {
        vgamem[i]=(char)0;
    }

    currpos=0;
}

static void update_cursor()
{
    outbyte(0x3d4,14);
    outbyte(0x3d5, ((currpos>>1)>>8)&0xff);
    outbyte(0x3d4,15);
    outbyte(0x3d5, ((currpos>>1)&0xff));
}
