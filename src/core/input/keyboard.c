#include "keyboard.h"
#include <stdint.h>
#include <core/cpu/io.h>

int is_shift = 0;
char *keycodes = "\e 1234567890-=\b\tqwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0\0\0 ";
char *keycodes_shift = "\e !@#$%^&*()_+\b\tQWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0\0\0 ";

char get_kb_key()
{
    char out = 0;
    while (1)
    {
        if (inb(0x64) & 0x1)
        {
            if (inb(0x60) == 0x2A)
                is_shift = 1;
            else if (inb(0x60) == 0xAA)
                is_shift = 0;

            if (is_shift)
                out = keycodes_shift[inb(0x60)];
            else
                out = keycodes[inb(0x60)];

            if (out != 0 && inb(0x60) < 60)
                break;
        }
    }
    return out;
}