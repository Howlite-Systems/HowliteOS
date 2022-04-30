#include "paging.h"
#include <core/video/console.h>
#include <utils/conversion.h>

extern uint32_t kernel_end;

void paging_init()
{
    // set each entry to not present
    for (int i = 0; i < 1024; i++)
    {
        // This sets the following flags to the pages:
        //   Other stuff -> 5 bits set to 0
        //   Supervisor: Only kernel-mode can access them -> 1 bit set to 0
        //   Write Enabled: It can be both read from and written to -> 1 bit set to 1
        //   Not Present: The page table is not present -> 1 bit set to 0
        page_directory[i] = 0b00000010;
    }

    // we will fill all 1024 entries in the table, mapping 4 megabytes
    for (int i = 0; i < 1024; i++)
    {
        // As the address is page aligned, it will always leave 12 bits zeroed.
        // Those bits are used by the attributes ;)
        first_page_table[i] = (i * 4096) | 0b011; // attributes: supervisor level, read/write, present.
    }

    // attributes: supervisor level, read/write, present
    page_directory[0] = ((unsigned int)first_page_table) | 0b011;

    load_page_dir(page_directory);
    enable_paging();
}