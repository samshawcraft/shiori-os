#include <stddef.h>
#include <stdint.h>

#include "interrupts/isr.h"
#include "interrupts/irq.h"
#include "interrupts/idt.h"
#include "interrupts/syscall.h"

#include "kernel/lib/include/stdlib.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"

#include "driver/vga_graphic_mode.h"
#include "driver/port.h"
#include "driver/pic.h"
#include "driver/acpi.h"
#include "driver/ps2.h"
#include "driver/ata.h"
#include "driver/keyboard.h"
#include "driver/mouse.h"

#include "kernel/gdt.h"
#include "kernel/tss.h"

void clear_vga(){
  unsigned char *vga_buffer = enable_graphic_256_xmode();
  int bg_color = 0x0f;
  int fg_color = 0x00;

  for (int y = 0; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++) {
      fg_color = 0x00;
      bg_color = 0x0f;
      if (vga_buffer == (unsigned char *) VGA_FRONT_BUFFER) {
        bg_color = 0x00;
        fg_color = 0x0f;
      }
      if (y == 0)
        put_a_pixel(x, y, bg_color, vga_buffer);
      else if (x == 0)
        put_a_pixel(x, y, bg_color, vga_buffer);
      else if (x == VGA_WIDTH - 1)
        put_a_pixel(x, y, bg_color, vga_buffer);
      else if (y == VGA_HEIGHT - 1)
        put_a_pixel(x, y, bg_color, vga_buffer);
      else
        put_a_pixel(x, y, 0x00, vga_buffer);
    }
  }
}

void switch_to_user_mode() {
  __asm__ volatile("cli");
  
  __asm__ volatile("mov $0x23, %ax");
  __asm__ volatile("mov %ax, %ds");
  __asm__ volatile("mov %ax, %es");
  __asm__ volatile("mov %ax, %fs");
  __asm__ volatile("mov %ax, %gs");

  __asm__ volatile("pushl $0x23");       
  __asm__ volatile("pushl $0x800000");   
  __asm__ volatile("pushf");             
  __asm__ volatile("pushl $0x1B");     
  __asm__ volatile("pushl $user_entry"); 
  __asm__ volatile("iret");

  __builtin_unreachable();
}

__attribute__((section(".user.text")))  
void user_entry() {
  char message[] = "Hello User Mode!"; 
  //puts(message);             //This will cause ISR 13: General Protection Fault
  //__asm__ volatile("cli");   //This will cause ISR 13: General Protection Fault
  __asm__ volatile( 
    "movl $103, %%eax \n\t"  
    "movl $1, %%ebx \n\t"  
    "movl %0, %%ecx \n\t"
    "movl $32, %%edx \n\t"
    "int $0x80 \n\t"
    "1: jmp 1b \n\t" 
    :
    : "r" (message)
    : "eax", "ebx", "ecx", "edx", "memory"
  );
}

void main() {
  init_gdt();
  init_tss();

  registers_isr();
  registers_irq();
  pic_first_init();
  register_the_idt();

  pic_unmask_irq(1);
  pic_unmask_irq(2);
  pic_unmask_irq(12);

  ps2_enable();
  install_keyboard();
  install_mouse();
  clear_vga();

  register_the_syscall_interrupt();
  switch_to_user_mode();
}

