#ifndef BONUX_ASMMACROES_H
#define BONUX_ASMMACROES_H

#define outbyte(port, value) __asm__("outb %%al, %%dx" :: "a"(value), "d"(port));
#define inbyte(port, tovar) __asm__("inb %%dx, %%al" : "=a" (tovar) : "d"(port)); 

#define ltr(n) __asm__("ltr %%ax"::"a"(n));

#define to_task(n) \
struct {long a,b;} tmp; tmp.b=n;\
__asm__("ljmp *%0"::"m"(tmp.a)); \


#define cli() __asm__("cli");
#define sti() __asm__("sti");

#define kernel_service() __asm__("int $0x80");

#define get_register(reg,var) get_ ## reg ## (var);

/* GP registers */
#define get_eax(var) __asm__("movl %%eax,%0":"=r"(var));
#define set_eax(var) __asm__("movl %0, %%eax"::"r"(var));
#define get_ebx(var) __asm__("movl %%ebx,%0":"=r"(var));
#define set_ebx(var) __asm__("movl %0, %%ebx"::"r"(var));
#define get_ecx(var) __asm__("movl %%ecx,%0":"=r"(var));
#define set_ecx(var) __asm__("movl %0, %%ecx"::"r"(var));
#define get_edx(var) __asm__("movl %%edx,%0":"=r"(var));
#define set_edx(var) __asm__("movl %0, %%edx"::"r"(var));
#define get_esp(var) __asm__("movl %%esp,%0":"=r"(var));
#define set_esp(var) __asm__("movl %0, %%esp"::"r"(var));
#define get_ebp(var) __asm__("movl %%ebp,%0":"=r"(var));
#define set_ebp(var) __asm__("movl %0, %%ebp"::"r"(var));
#define get_esi(var) __asm__("movl %%esi,%0":"=r"(var));
#define set_esi(var) __asm__("movl %0, %%esi"::"r"(var));
#define get_edi(var) __asm__("movl %%edi,%0":"=r"(var));
#define set_edi(var) __asm__("movl %0, %%edi"::"r"(var));
#define get_eip(var) __asm__("movl %%eip,%0":"=r"(var));
#define set_eip(var) __asm__("movl %0, %%eip"::"r"(var));

/* Segment registers */
#define get_cs(var) __asm__("mov %%cs,%0":"=r"(var));
#define set_cs(var) __asm__("mov %0, %%cs"::"r"(var));
#define get_ds(var) __asm__("mov %%ds,%0":"=r"(var));
#define set_ds(var) __asm__("mov %0, %%ds"::"r"(var));
#define get_ss(var) __asm__("mov %%ss,%0":"=r"(var));
#define set_ss(var) __asm__("mov %0, %%ss"::"r"(var));
#define get_es(var) __asm__("mov %%es,%0":"=r"(var));
#define set_es(var) __asm__("mov %0, %%es"::"r"(var));
#define get_fs(var) __asm__("mov %%fs,%0":"=r"(var));
#define set_fs(var) __asm__("mov %0, %%fs"::"r"(var));
#define get_gs(var) __asm__("mov %%gs,%0":"=r"(var));
#define set_gs(var) __asm__("mov %0, %%gs"::"r"(var));

/* Debug registers */
#define get_dr0(var) __asm__("mov %%dr0,%0":"=r"(var));
#define get_dr1(var) __asm__("mov %%dr1,%0":"=r"(var));
#define get_dr2(var) __asm__("mov %%dr2,%0":"=r"(var));
#define get_dr3(var) __asm__("mov %%dr3,%0":"=r"(var));
#define get_dr6(var) __asm__("mov %%dr6,%0":"=r"(var));
#define get_dr7(var) __asm__("mov %%dr7,%0":"=r"(var));

/* Control and flag registers */
#define set_cr0(var) __asm__("movl %0, %%cr0"::"r"(var));
#define get_cr0(var) __asm__("movl %%cr0,%0":"=r"(var));
#define get_cr3(var) __asm__("movl %%cr3,%0":"=r"(var));
#define set_cr3(var) __asm__("movl %0, %%cr3"::"r"(var));
#define get_cr4(var) __asm__("movl %%cr4,%0":"=r"(var));
#define set_cr4(var) __asm__("movl %0, %%cr4"::"r"(var));
#define get_eflags(var) __asm__("pushfl\n\t" \
                "popl %0\n\t" \
                 :"=r"(var));
#define set_eflags(var) __asm__("popfl\n\t");

#define get_tr(var) __asm__("mov %%tr,%0":"=r"(var));
#define set_tr(var) __asm__("mov %0, %%tr"::"r"(var));

/* Blahh...Real mode stuff */
#define getmemsize(to) __asm__("movb $0x88, %%ah\n\t" \
                       "int $0x15\n\t" \
                       "movw %%ax, %%dx\n\t" : "=d" (to) :: "%eax");


#endif
