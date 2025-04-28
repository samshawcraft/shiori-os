CC = i686-elf-gcc.exe
LD = i686-elf-ld.exe
PY = python.exe

KERNEL_SRC = kernel/kernel.c \
						kernel/gdt.c \
						kernel/tss.c \
						driver/vga_text_mode.c \
						driver/vga_graphic_mode.c \
						driver/port.c \
						driver/pic.c \
						driver/rsdp.c \
						driver/acpi.c \
						driver/ps2.c \
						driver/keyboard.c \
						driver/mouse.c \
						driver/ata.c 
MODULE_SRC = $(wildcard modules/*.c)
SYSCALL_SRC = $(wildcard kernel/syscalls/*.c)
LIB_SRC = $(wildcard kernel/lib/stdio/*.c kernel/lib/stdlib/*.c kernel/lib/string/*.c)
INTERRUPTS_SRC = interrupts/idt.c \
								interrupts/isr.c \
								interrupts/irq.c \
								interrupts/syscall.c

KERNEL_OBJ = $(KERNEL_SRC:.c=.o)
MODULE_OBJ = $(MODULE_SRC:.c=.o)
SYSCALL_OBJ = $(SYSCALL_SRC:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)
INTERRUPTS_OBJ = $(INTERRUPTS_SRC:.c=.o)

interrupt_handler.o: interrupts/interrupt_handler.asm
	nasm $< -f elf -o $@

syscall_handler.o: interrupts/syscall_handler.asm
	nasm $< -f elf -o $@

gdt_flush.o: kernel/gdt_flush.asm
	nasm $< -f elf -o $@

tss_flush.o: kernel/tss_flush.asm
	nasm $< -f elf -o $@

%.o: %.c
	$(CC) -ffreestanding -nostdlib -c $< -o $@ -I . -Wno-incompatible-pointer-types

kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf -o $@

kernel.bin: kernel_entry.o $(KERNEL_OBJ) $(MODULE_OBJ) $(SYSCALL_OBJ) $(LIB_OBJ) $(INTERRUPTS_OBJ) \
						interrupt_handler.o syscall_handler.o gdt_flush.o tss_flush.o 
	$(LD) -nostdlib -o $@ -Ttext 0x8000 $^ --oformat binary

kernel.elf: kernel_entry.o $(KERNEL_OBJ) $(MODULE_OBJ) $(SYSCALL_OBJ) $(LIB_OBJ) $(INTERRUPTS_OBJ) \
						interrupt_handler.o syscall_handler.o gdt_flush.o tss_flush.o 
	$(LD) -nostdlib -o $@ -Ttext 0x8000 $^

boot.bin: bootloader/boot.asm
	nasm $< -f bin -o $@

image_os: boot.bin kernel.bin
	cat $^ > $@

calculate_kernel_size: kernel.bin
	$(PY) ./calculate_kernel_size.py

image: calculate_kernel_size image_os

run:
	qemu-system-i386 \
  -drive file=image_os,format=raw,index=0,media=disk \
  -drive file=mydisk.qcow2,format=qcow2,index=1,media=disk \
  -boot c \
	-serial stdio \
	-monitor telnet:localhost:9312,server,nowait 

buildrun: clean image run

debug: clean image kernel.elf
	qemu-system-i386 -s -S \
	-drive file=image_os,format=raw,index=0,media=disk \
  -drive file=mydisk.qcow2,format=qcow2,index=1,media=disk \
  -boot c \
  -serial stdio \
	-monitor telnet:localhost:9312,server,nowait &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	rm -f *.o
	rm -f *.bin
	rm -f kernel/*.o
	rm -f kernel/lib/*/*.o
	rm -f kernel/syscalls/*.o
	rm -f interrupts/*.o
	rm -f driver/*.o
	rm -f modules/*.o
	rm -f image_os
	rm -f kernel.elf
