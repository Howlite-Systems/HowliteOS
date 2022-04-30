// https://wiki.osdev.org/Paging
// https://wiki.osdev.org/Setting_Up_Paging
#pragma once
#include <stdint.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t first_page_table[1024] __attribute__((aligned(4096)));

extern void load_page_dir(uint32_t*);
extern void enable_paging();

void paging_init();