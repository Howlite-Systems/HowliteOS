#include "memory.h"

void* memset(void* dest, int c, size_t n)
{
    n /= 4;
    asm volatile("cld; rep stosb" : "+D"(dest), "+c"(n) : "a"(c) : "memory");
    return dest;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    asm volatile ("cld; rep movsb" : "+c" (n), "+S" (src), "+D" (dest) :: "memory");
    return dest;
}

void* memmove(void* dest, const void* src, size_t n)
{
    return memcpy(dest, src, n);
}

void* kmalloc(uint32_t size, int align, void* phys)
{
    if (align == 1 && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
    {
        // Align it.
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    // if (phys)
    // {
    //     *phys = placement_address;
    // }

    uint32_t tmp = placement_address;
    placement_address += size;
    return (void*)tmp;
}