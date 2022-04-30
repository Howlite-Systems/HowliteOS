#include "isr.h"
#include <core/video/console.h>
#include <utils/conversion.h>

char adr_str_buffer[16];
void exc_page_fault(registers_t regs)
{
   // A page fault has occurred.
   // The faulting address is stored in the CR2 register.
   uint32_t faulting_address;
   asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

   // The error code gives us details of what happened.
   int present = !(regs.err_code & 0x1);   // Page not present
   int rw = regs.err_code & 0x2;           // Write operation?
   int us = regs.err_code & 0x4;           // Processor was in user-mode?
   int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
   int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

   // Output an error message.
   print("Page fault! ( ");
   if (present) {print("present ");}
   if (rw) {print("read-only ");}
   if (us) {print("user-mode ");}
   if (reserved) {print("reserved ");}
   print(") at 0x");
   print(itoa(faulting_address, adr_str_buffer, 16));
   print("\n");

   while (1);
}

// This gets called from our ASM interrupt handler stub.
char buffer[3];
void isr_handler(registers_t regs)
{
   print("\nRecieved interrupt: ");
   print(itoa(regs.int_no, buffer, 10));
   print(" (0x");
   print(itoa(regs.int_no, buffer, 16));
   print(").");
   print('\n');

   switch (regs.int_no)
   {
   case 14:
      exc_page_fault(regs);
      break;
   
   default:
      while(1);
      break;
   }
}