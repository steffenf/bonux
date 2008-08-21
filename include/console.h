#ifndef BONUX_CONSOLE_H
#define BONUX_CONSOLE_H

#include "tty.h"

#define LINES 25
#define COLUMNS 80
#define CONSOLE_PROMPT "Bonux console# "

extern void init_console();
extern void write_console(const struct tty_st* tty);

#endif
