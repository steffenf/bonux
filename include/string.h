#ifndef BONUX_STRING_H
#define BONUX_STRING_H

#define NULL (void*)0

typedef unsigned long int size_t;

extern void* memcpy(void* dst, const void* src, size_t n);
extern void* memset(void* dst, unsigned int val, size_t n);
extern size_t strlen(const char* s);
#endif
