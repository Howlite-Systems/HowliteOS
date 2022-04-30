#include "console.h"
#include <core/input/keyboard.h>
#include <core/memory/memory.h>

uint16_t *vga_buffer = (uint16_t *)0xB8000;

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

int cursor_x = 0;
int cursor_y = 0;
uint8_t color_fg = 0xF;
uint8_t color_bg = 0x0;

// increment x
static void inc_x()
{
    cursor_x++;
    if (cursor_x == VGA_WIDTH)
    {
        cursor_x = 0;
        cursor_y++;
    }
}
// decrement x
static void dec_x()
{
    cursor_x--;
    if (cursor_x == -1)
    {
        cursor_x = VGA_WIDTH - 1;
        cursor_y--;
    }
}

static void update_cursor_pos()
{
    uint16_t pos = cursor_y * VGA_WIDTH + cursor_x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

static void scroll()
{
    cursor_y = VGA_HEIGHT - 1;
    cursor_x = 0;
    memcpy(0xB8000, 0xB8000 + VGA_WIDTH * 2, VGA_WIDTH * VGA_HEIGHT * 2 - VGA_WIDTH * 2);
    for (int i = 0; i < VGA_WIDTH; i++)
        vga_buffer[VGA_WIDTH * (VGA_HEIGHT-1) + i] = ((uint16_t)color_bg << 12 | color_fg << 8) | ' ';
    update_cursor_pos();
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
        inc_x();
        break;
    }
    if (cursor_y >= VGA_HEIGHT)
        scroll();
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

char buf[256];
char* read_line()
{
    memset(&buf, 0, 64);

    int index = 0;
    char ch = 0;
    while(ch = get_kb_key())
    {           
        if (ch == '\n')
            break;
        if (ch == '\b')
        {
            index--;
            if (index == -1) index = 0;
            else
            {
                dec_x();
                put_char(' ');
                dec_x();
                update_cursor_pos();

                buf[index] = '\0';
            }          
        }
        else
        {
            put_char(ch);
            buf[index] = ch;
            index++;
        }            
    }
    put_char('\n');

    return buf;
}