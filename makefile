SOURCES=$(shell find . -name '*.c')

CC=i686-elf-gcc
CFLAGS=-Isrc/ -fno-use-cxa-atexit -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -Wno-write-strings -Wno-unused-variable -w -Wno-narrowing -Wno-sign-compare -Wno-type-limits -Wno-unused-parameter -Wno-missing-field-initializers
C_FILES_OUT = $(SOURCES:.c=.o)

LD=i686-elf-gcc
AS=i686-elf-as
NASM=nasm
ASFLAGS=-felf32

LINK_SOURCES=$(shell find . -name '*.o')


all: as $(C_FILES_OUT) link clean_objects run-kernel
as:
	$(AS) 'src/asm/boot.asm' -o 'src/asm/boot.o'
	$(NASM) $(ASFLAGS) 'src/asm/gdt.asm' -o 'src/asm/gdt.o'
	$(NASM) $(ASFLAGS) 'src/asm/interrupts.asm' -o 'src/asm/interrupts.o'
	$(NASM) $(ASFLAGS) 'src/asm/realmode.asm' -o 'src/asm/realmode.o'
	$(NASM) $(ASFLAGS) 'src/asm/paging.asm' -o 'src/asm/paging.o'
	$(NASM) $(ASFLAGS) 'src/asm/tss.asm' -o 'src/asm/tss.o'
link:
	$(LD) -w -T 'linker.ld' -o 'kernel.bin' -ffreestanding -O2 -nostdlib $(LINK_SOURCES) -lgcc	

clean:
	-rm -Rf $(shell find . -name '*.o') $(shell find . -name '*.a') $(shell find . -name '*.bin') $(shell find . -name '*.iso')

clean_objects:
	-rm -Rf $(shell find . -name '*.o') $(shell find . -name '*.a') 

run-kernel:
	qemu-system-i386.exe -kernel kernel.bin -serial stdio -vga std -no-reboot -no-shutdown -d int -M smm=off