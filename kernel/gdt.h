#ifndef H_GDT
#define H_GDT

#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void gdt_set_gate(int, uint32_t, uint32_t, uint8_t, uint8_t);
void init_gdt(void);

#endif