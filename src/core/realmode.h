#pragma once
#include <stdint.h>
typedef struct
{
    uint16_t DI, SI, BP, SP, BX, DX, CX, AX;
    uint16_t GS, FS, ES, DS, EFlags;
} __attribute__((packed)) registers16_t;

void _int_16(uint8_t interrupt, registers16_t* regs);