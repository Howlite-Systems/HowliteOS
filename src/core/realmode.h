#pragma once
#include <stdint.h>
typedef struct
{
    uint16_t DI, SI, BP, SP, BX, DX, CX, AX;
    uint16_t GS, FS, ES, DS, EFlags;
} registers16_t __attribute__((packed));

void _int_16(uint8_t interrupt, registers16_t* regs);