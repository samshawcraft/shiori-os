#ifndef H_IRQ
#define H_IRQ

#include <stddef.h>
#include "interrupts/isr.h"

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);


void registers_irq(void);
void install_irq_handler(int irq, void (*handler)(reg_t *));
void irq_handler(reg_t *regs);

#endif