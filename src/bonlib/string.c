#include "string.h"

void* memcpy(void* dst, const void* src, size_t n) 
{
    unsigned char* dsttmp=(unsigned char*)dst;
    unsigned char* srctmp=(unsigned char*)src;

    while(n--) {
        *dsttmp++=*srctmp++;
    }

    return dst;
}

void* memset(void* dst, unsigned int val, size_t n) 
{
    unsigned char* dsttmp=(unsigned char*)dst;
    unsigned char valtmp=(unsigned char)val;

    while(n--) {
        *dsttmp++=valtmp;
    }

    return dst;
}

size_t strlen(const char* s)
{
    size_t i=0;

    while(s[i] != 0)
        i++;

    return i;
}
