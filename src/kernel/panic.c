#include "print.h"

#include "panic.h"

void panic(const char* message)
{
    dumpcpu();
    printk(message);
    for(;;);
}

