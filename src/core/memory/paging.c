#include "paging.h"

void paging_init()
{
    page_dir_ptr_table[0] = (uint64_t)&page_dir | 1; // set the page directory into the PDPT and mark it present
    page_dir[0] = 0b10000011; //Address=0, 2MIB, RW and present

    asm volatile ("movl %%cr4, %%eax; bts $5, %%eax; movl %%eax, %%cr4" ::: "eax"); // set bit5 in CR4 to enable PAE		 
    asm volatile ("movl %0, %%cr3" :: "r" (&page_dir_ptr_table)); // load PDPT into CR3
    asm volatile ("movl %%cr0, %%eax; orl $0x80000000, %%eax; movl %%eax, %%cr0;" ::: "eax");
}