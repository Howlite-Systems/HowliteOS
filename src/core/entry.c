#include "entry.h"

#include <core/video/console.h>

#include <core/cpu/gdt.h>
#include <core/cpu/interrupts/idt.h>

#include <core/memory/memory.h>
#include <core/memory/paging.h>

#include <utils/conversion.h>

char buf[20];
void kernel_main()
{
    clear();

    gdt_init();
    idt_init();
    paging_init();

    while (1)
    {
        print("Input: ");
        read_line();
    }
}