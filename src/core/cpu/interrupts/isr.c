#include "isr.h"
#include <core/video/console.h>
#include <utils/conversion.h>

// This gets called from our ASM interrupt handler stub.
char buffer[3];
void isr_handler(registers_t regs)
{
   print("Recieved interrupt: ");
   print(itoa(regs.int_no, buffer, 10));
   print(" (0x");
   print(itoa(regs.int_no, buffer, 16));
   print(").");
   print('\n');

   while (1);
}