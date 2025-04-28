#include "idt.h"

idt_section_t idt[NUMBER_OF_INTERRUPTS] = {0};
idt_t idt_params = {0};

void register_an_interrupt(int n, unsigned int handler, unsigned short selector, unsigned char attributes)
{
    if(n >= NUMBER_OF_INTERRUPTS) return;
    
    idt[n].offset_low = (unsigned short)(handler & 0xFFFF);
    idt[n].selector = selector; 
    idt[n].zero = 0x00;
    idt[n].attributes = attributes;
    idt[n].offset_high = (unsigned short)((handler >> 16) & 0xFFFF);
}

void register_the_idt(void)
{
    idt_params.size = (sizeof(idt_section_t) * NUMBER_OF_INTERRUPTS) - 1;
    idt_params.addr = (unsigned int) &idt;

    __asm__ volatile("lidt %0" : : "m" (idt_params));
    __asm__ volatile("sti");
}

static void default_handler()
{
    __asm__ volatile("cli; hlt");  // Halt on unexpected interrupts
}