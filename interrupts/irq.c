#include "interrupts/idt.h"
#include "interrupts/irq.h"
#include "interrupts/isr.h"
#include "driver/pic.h"
#include "driver/port.h"
#include <stddef.h>

static void (*irq_handlers[16])(reg_t *) = {NULL};

void registers_irq(void)
{
    register_an_interrupt(0x20, (unsigned int)irq0, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x21, (unsigned int)irq1, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x22, (unsigned int)irq2, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x23, (unsigned int)irq3, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x24, (unsigned int)irq4, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x25, (unsigned int)irq5, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x26, (unsigned int)irq6, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x27, (unsigned int)irq7, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x28, (unsigned int)irq8, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x29, (unsigned int)irq9, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x2A, (unsigned int)irq10, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x2B, (unsigned int)irq11, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x2C, (unsigned int)irq12, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x2D, (unsigned int)irq13, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x2E, (unsigned int)irq14, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
    register_an_interrupt(0x2F, (unsigned int)irq15, CODE_DESC_SELECTOR, IDT_INTERRUPT_GATE);
}


void install_irq_handler(int irq,  void (*handler)(reg_t *))
{
    irq_handlers[irq] = handler;
}

void irq_handler(reg_t *test)
{
    if (irq_handlers[test->code] != NULL) {
        void (*fun)(void) = (void (*)(void)) irq_handlers[test->code];
        fun();
    }
    pic_send_eio(test->code);
}