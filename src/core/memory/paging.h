#pragma once
#include <stdint.h>

uint64_t page_dir_ptr_table[4] __attribute__((aligned(0x20)));
uint64_t page_dir[512] __attribute__((aligned(0x1000))); // decimal 4096 -> they need to be page-aligned

void paging_init();