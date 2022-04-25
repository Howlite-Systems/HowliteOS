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