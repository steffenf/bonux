#include "asmmacroes.h"
#include "tasks.h"
#include "print.h"

#include "mem.h"

/* Create one pde for every process. Create first pte for every process. */
unsigned long pde[MAX_TASKS][1024]  __attribute__ ((aligned (PAGE)));
unsigned long pte0[MAX_TASKS][1024]  __attribute__ ((aligned (PAGE)));

/* A bit map supporting 33 megs of memory */
static unsigned char phys_page_bitmap[8192]; 

static unsigned int allocate_physical_page();
static void free_physical_page(const unsigned int page);
 
/* This function sets up a PDE for all tasks and the first PTE for all tasks. The first PTE for all tasks identity maps the first 4mb of phyical memory. */
/* After initialization some flags are set in control registers, and paging is finally turned on */
void init_paging() 
{
    unsigned long cr=0;
    int i,j;

    /* Set the first 1024 pages to bizzi, because the first four megs of physical memory are busy */
    for(i=0;i<8192;i++) {
        phys_page_bitmap[i]=(i<1024)?1:0;
    }

    /* Initialize alle page table pointer entries with the "Read/Write" flag set. */
    for(i=0;i<MAX_TASKS;i++) {
        for(j=0;j<1024;j++) {
            pde[i][j]=0|0x2;
    }
}

    /* The first entry inn pde points to our statically created page table covering the first 8mb of physical addresses. All processes have this mapping.  */
    for(i=0;i<MAX_TASKS;i++) {
        pde[i][0] = (unsigned long)(pte0[i]);   /*First entry points to the static ptable */
        pde[i][0] |= 0x3;                       /* "Read/Write" and "Present */
    }

/* Initialize the entries in pte0 for all processes. Identity mapping the first 4mb of memory. */  
    for(i=0;i<MAX_TASKS;i++) {
        for(j=0;j<1024;j++) {
            pte0[i][j]=j*PAGE; /* Identity mapping */
            pte0[i][j]|=0x3;  /* "Read/Write" and "Present" */ 
        }
    }

    /* Clear bit 4 of CR4  (PSE) and bit 5 of CR4 (PAE) */
    get_cr4(cr);
    cr&=0xffffffcf;
    set_cr4(cr);

    /* Set CR3 to physical address of bottom of kernel PDE */
    set_cr3(((unsigned long)(pde[ADAMEVA_TASK])));

    /* Set bit 31 of CR0 (PG) */
    get_cr0(cr);
    cr|=0x80000000;  /* PE flag must also be set anyhows */
    set_cr0(cr);
}

static unsigned int allocate_physical_page() {
    int i;

    for(i=0;i<8192;i++) {
        if(phys_page_bitmap[i]==0) {
            phys_page_bitmap[i]=1;
            return i;
        }
   }

    panic("No more physical memory available, and Bonux can't page to disk");
}

static void free_physical_page(const unsigned int page) {
    phys_page_bitmap[page]=0;
}
