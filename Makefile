OBJDIR=./obj/
BINDIR=./bin/
SOURCEFILES:= $(shell find . -name '*.c')
OBJFILES:= $(shell find . -name '*.c' | sed -e 's/\.c/.o/g' | while read f;do basename $$f;done | xargs echo)

vpath %.c src src/boot src/interrupts src/init src/drivers src/bonlib src/mem src/kernel
vpath %.h include
vpath %.o obj

AC=nasm
AFLAGS=-f elf

CC=gcc
CFLAGS=-c -fomit-frame-pointer -fno-builtin 
CPPFLAGS=-I include

all: $(BINDIR)bonux.bin
	mv *.o $(OBJDIR)

$(BINDIR)bonux.bin: $(BINDIR)bonuxkernel.bin $(BINDIR)bootblock.bin

$(BINDIR)bonuxkernel.bin: setup32.o low_interrupthandlers.o $(OBJFILES)
	ld -M -T link.ld $^ -o $@

setup32.o: src/boot/setup32.s
	$(AC) $(AFLAGS) $^ -o $@

low_interrupthandlers.o: src/interrupts/low_interrupthandlers.s
	$(AC) $(AFLAGS) $^ -o $@

$(BINDIR)bootblock.bin:
	$(AC) src/boot/bootblock.s -o $@

.PHONY: .depend
.depend:
	$(CC) -MM -DPTHREADS $(SOURCEFILES) $(CPPFLAGS) > .depend
include .depend

.PHONY: writetodisk
writetodisk:
	cat bin/bootblock.bin bin/bonuxkernel.bin > bin/bonux.bin
	dd if=bin/bonux.bin of=/dev/sda1

.PHONY: clean
clean:
	rm -rf obj/*.o bin/*.bin
