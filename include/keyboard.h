#ifndef BONUX_KEYBOARD_H
#define BONUX_KEYBOARD_H

#define UNKNOWN 0x00
#define ESCAPE 0x01
#define BACKSPACE 0x0e
#define LCTRL 0x1d
#define LSHIFT 0x2a
#define RSHIFT 0x36
#define PRINTSCREEN 0x37 
#define LALT 0x38
#define CAPSLOCK 0x39
#define F1 0x3b
#define F2 0x3c
#define F3 0x3d
#define F4 0x3e
#define F5 0x3f
#define F6 0x40
#define F7 0x41
#define F8 0x42
#define F9 0x43
#define F10 0x44
#define NUMLOCK 0x45
#define SCROLLOCK 0x46
#define KPHOME 0x47
#define KPUP 0x48
#define KPPGUP 0x49
#define KPMINUS 0x4a
#define KPLEFT 0x4b
#define KPCENTER 0x4c
#define KPRIGHT 0x4d
#define KPPLUS 0x4e
#define KPEND 0x4e
#define KPDOWN 0x50
#define KPPGDOWN 0x51
#define KPINSERT 0x52
#define KPDEL 0x53
#define SYSREQ 0x54
#define STRANGER1 0x55
#define STRANGER2 0x56
#define STRANGER3 0x57

#define FLAG_SHIFT 0x01

extern void init_keyboard();
extern void read_keyboard();

#endif
