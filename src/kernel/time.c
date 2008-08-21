#include "print.h"
#include "asmmacroes.h"
#include "tasks.h"

#include "time.h"

#define BCD_TO_BIN(val) ((val)=((val)&15) + ((val)>>4)*10)
#define BIN_TO_BCD(val) ((val)=(((val)/10)<<4) + (val)%10)

static unsigned long unixtime=0;

/* Utterly naive */
void init_unix_time() {
    unsigned char sec;
    unsigned char min;
    unsigned char hour; 
    unsigned char day; 
    unsigned char month;
    unsigned char year;
    
    outbyte(0x70,0x00);
    inbyte(0x71,sec);
    
    outbyte(0x70,0x02);
    inbyte(0x71,min);

    outbyte(0x70,0x04);
    inbyte(0x71,hour);

    outbyte(0x70,0x07);
    inbyte(0x71,day);

    outbyte(0x70,0x08);
    inbyte(0x71,month);

    outbyte(0x70,0x09);
    inbyte(0x71,year);

    /* Now we have BCD, convert to real integers */
    BCD_TO_BIN(sec);
    BCD_TO_BIN(min);
    hour = (hour & 0xf) + ((hour&0x70)>>4)*10 + (hour&0x80); 
    BCD_TO_BIN(day);
    BCD_TO_BIN(month);
    BCD_TO_BIN(year);

    /* Calculate unix time */
    unsigned long fullyeardays = year * 365 + ((year-1)/4) + 1; 
    static unsigned short daysbeforemonth[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    unsigned thisyeardays = daysbeforemonth[month-1] + day  - (((year%4)==0 && month > 2) ? 0 : 1);
    unsigned long date = fullyeardays + thisyeardays + 10957; 
    unixtime= sec + 60 * (min + 60 * (hour + 24 * date)); 
}

void update_unix_time() {
    if((ticks%HERTZ)==0) {
        unixtime++;
    }
}

unsigned long get_unix_time() {
    return unixtime;
}

void get_date_and_time(struct st_time* time) {
    unsigned long tmp = unixtime;

    time->second = (tmp%60);                 
    time->minute = (tmp/=60) % 60;         
    time->hour = (tmp/=60) % 24;          
}

void chill(const unsigned long millis) {
    unsigned long ticksend = ticks + (millis/10);
    while(ticks<ticksend);
}
