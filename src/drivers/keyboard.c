#include "asmmacroes.h"
#include "tty.h"
#include "keyboard.h"


static const unsigned char scan_to_ascii_noshift[] =
{0,0,'1','2','3','4','5','6','7','8','9','0','-','=',0,'\t',        /* 0x00-0x0F */
 'q','w','e','r','t','y','u','i','o','p','[',']','\r',0,'a','s',    /* 0x10-0x1F */
 'd','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v',   /* 0x20-0x2F */
 'b','n','m',',','.','/',0,0,0,' ',0,0,0,0,0,0,                     /* 0x30-0x3F */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                                   /* 0x40-0x4F */
 0,0,0,0,0,0,0,0};                                                  /* 0X50-0x57 */

static const unsigned char scan_to_ascii_shift[] =
{0,0,'!','@','#','$','%','^','&','*','(',')','_','+',0,'\t',        /* 0X00-0x0F */
 'Q','W','E','R','T','Y','U','I','O','P','{','}','\r',0,'A','S',    /* 0x10-0x1F */
 'D','F','G','H','J','K','L',':','"','~',0,'|','Z','X','C','V',     /* 0x20-0x2F */
 'B','N','M','<','>','?',0,0,0,' ',0,0,0,0,0,0,                     /* 0x30-0x3F */
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                                   /* 0x40-0x4F */
 0,0,0,0,0,0,0,0};                                                  /* 0X50-0x57 */

static void change_special_flags(unsigned char sc);
static unsigned char flags;

void init_keyboard()
{
}

void read_keyboard()
{
    unsigned char kb_byte;
    unsigned char kb_char;

    inbyte(0x60,kb_byte);

    if((kb_byte&0x80)!=0) {
        change_special_flags(kb_byte);
        goto end;
    }
      
    kb_char=((flags&FLAG_SHIFT)==0)?scan_to_ascii_noshift[kb_byte]:scan_to_ascii_shift[kb_byte];

    if(kb_char==0) {
        change_special_flags(kb_byte);
    } else {
        /* echo keyboard input to console */
        tty_pushwrite(kb_char,CONSOLE_TTY);
        tty_pushread(kb_char,CONSOLE_TTY);
    }

end:
    return;
}

static void change_special_flags(unsigned char sc)
{
    unsigned char breaked = (sc&0x80);

    switch (sc&(~0x80)) {
        case LSHIFT:
        case RSHIFT: 
                (breaked==0)?(flags|=FLAG_SHIFT):(flags&=(~FLAG_SHIFT));
            break;
        default:
            break;
    }
    return;
}

