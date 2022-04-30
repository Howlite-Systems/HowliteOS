#pragma once
#include "paging.h"
#include <stdint.h>
#include <stddef.h>

void* memset(void* dest, int c, size_t n);
void* memcpy(void* dest, const void* src, size_t n);
void* memmove(void* dest, const void* src, size_t n);

uint32_t placement_address; //will be casted to void*
void* kmalloc(uint32_t size, int align, void* phys);