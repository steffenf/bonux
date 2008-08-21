#ifndef BONUX_TIME_H
#define BONUX_TIME_H

extern void init_unix_time();
extern void update_unix_time();
extern unsigned long get_unix_time();
extern void chill(const unsigned long millis);

struct st_time {
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
    unsigned short year;
};

extern void get_date_and_time(struct st_time* time);

#endif

