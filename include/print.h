#ifndef BONUX_PRINT_H
#define BONUX_PRINT_H

extern void printk(const char* message);
extern void printbyte(const unsigned char nibble);
extern void printnibble(const unsigned char byte);
extern void printregister(const char* name, const unsigned long value);
extern void dumpcpu();
#endif
