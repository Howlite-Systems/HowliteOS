#include "console.h"
#include <core/input/keyboard.h>

uint16_t *vga_buffer = (uint16_t *)0xB8000;

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int cursor_x = 0;
int cursor_y = 0;
uint8_t color_fg = 0xF;
uint8_t color_bg = 0x0;

static void update_cursor_pos()
{
    uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

static void put_char(char c)
{
    switch (c)
    {
    case '\n':
        cursor_x = 0;
        cursor_y++;
        break;
    default:
        vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = ((uint16_t)color_bg << 12 | color_fg << 8) | c;
        cursor_x++;
        break;
    }
    if (cursor_x == VGA_WIDTH)
    {
        cursor_x = 0;
        cursor_y++;
    }
    update_cursor_pos();
}

void clear()
{
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        put_char(' ');
    cursor_x = 0;
    cursor_y = 0;
    update_cursor_pos();
}

void print(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        put_char(str[i]);
}

char* read_line()
{
    char ch = 0;
    while(ch = get_kb_key())
    {           
        if (ch == '\n')
            break;
        put_char(ch);
    }
    put_char('\n');
}