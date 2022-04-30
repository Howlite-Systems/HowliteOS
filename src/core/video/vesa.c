#include "vesa.h"
#include <core/realmode.h>
#include <core/memory/memory.h>
#include <core/entry.h>

#define LNG_PTR(seg, off) ((seg << 4) | off)
#define REAL_PTR(arr) LNG_PTR(arr[1], arr[0])
#define SEG(addr) (((uint32_t)addr >> 4) & 0xF000)
#define OFF(addr) ((uint32_t)addr & 0xFFFF)

vesa_mode_info_t vesa_mode_info;
vesa_info_t      vesa_info;
uint32_t         vesa_width, vesa_height;
uint32_t*        vesa_buffer;
uint32_t         vesa_buffer_size;

void vesa_probe()
{
    // copy data from memory into structure
    // vesa_mode_info_t* ptr = (vesa_mode_info_t*)mbptr->vbe_mode_info;
    // memcpy(&vesa_mode_info, ptr, sizeof(vesa_mode_info_t));

    // vesa_info_t* info_ptr = (vesa_info_t*)0x80000;
    // memcpy(&vesa_info, info_ptr, sizeof(vesa_info_t));

    // registers16_t regs;
    // regs.AX = 0x4F00;
    // regs.ES = 0x8000;
    // regs.DI = 0x0000;
    // _int_16(0x10, &regs);

    // // set properties
    // vesa_width  = vesa_mode_info.width;
    // vesa_height = vesa_mode_info.height;
    // vesa_buffer = (uint32_t*)vesa_mode_info.framebuffer;
    // vesa_buffer_size = vesa_width * vesa_height * 4;
}