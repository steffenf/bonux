#ifndef BONUX_MEM_H
#define BONUX_MEM_H

#define LOW_MEM_START       0x00000000     /* Low memory start */
#define KERNEL_STACK_START  0x0009efff     /* Kernel stack in low memory, grows towards memory cell 0 */
#define HI_MEM_START        0x0009f000     /* Hi memory start */
                                           /* This area is like..very...reserved */ 
#define EXT_MEM_START       0x00200000     /* Start of open extended memory. This is where the  kernel starts its life... */

#define PAGE 4096

/* One 4096-sized page for page directory entries. This stuff must be 4096 aligned */
extern unsigned long pde [MAX_TASKS][PAGE/sizeof(unsigned long)];
/* One 4096-sized static page for kernel mapping . This stuff must be 4096 aligned */
extern unsigned long pte0[MAX_TASKS][PAGE/sizeof(unsigned long)];

extern void  init_paging();


#endif
