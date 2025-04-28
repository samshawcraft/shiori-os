#include "idt.h"
#include "isr.h"
#include "kernel/lib/include/stdio.h"

void registers_isr(void)
{
    register_an_interrupt(0x0, (unsigned int) isr0, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x1, (unsigned int) isr1, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x2, (unsigned int) isr2, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x3, (unsigned int) isr3, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x4, (unsigned int) isr4, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x5, (unsigned int) isr5, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x6, (unsigned int) isr6, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x7, (unsigned int) isr7, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x8, (unsigned int) isr8, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x9, (unsigned int) isr9, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0xA, (unsigned int) isr10, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0xB, (unsigned int) isr11, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0xC, (unsigned int) isr12, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0xD, (unsigned int) isr13, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0xE, (unsigned int) isr14, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0xF, (unsigned int) isr15, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x10, (unsigned int) isr16, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x11, (unsigned int) isr17, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x12, (unsigned int) isr18, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x13, (unsigned int) isr19, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x14, (unsigned int) isr20, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x15, (unsigned int) isr21, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x16, (unsigned int) isr22, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x17, (unsigned int) isr23, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x18, (unsigned int) isr24, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x19, (unsigned int) isr25, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x1A, (unsigned int) isr26, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x1B, (unsigned int) isr27, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x1C, (unsigned int) isr28, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x1D, (unsigned int) isr29, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x1E, (unsigned int) isr30, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x1F, (unsigned int) isr31, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
}

void isr_handler(reg_t *test)
{
    printf("ISR Called %d %x\n\r", test->code, test->error);
}