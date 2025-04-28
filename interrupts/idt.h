#ifndef H_IDT
#define H_IDT

#define NUMBER_OF_INTERRUPTS 256  
#define IDT_INTERRUPT_GATE 0x8E   // 32-bit interrupt gate (DPL=0)
#define IDT_USER_GATE      0xEE   // 32-bit interrupt gate (DPL=3)
#define CODE_DESC_SELECTOR 0x08
#define DATA_DESC_SELECTOR 0x10

typedef struct {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char attributes;
    unsigned short offset_high;
} __attribute__((packed)) idt_section_t;

typedef struct {
    unsigned short size;
    unsigned int addr;
} __attribute__((packed)) idt_t;

// Updated to include attributes parameter
void register_an_interrupt(int n, unsigned int, unsigned short, unsigned char);
void register_the_idt(void);
static void default_handler(void);

#endif