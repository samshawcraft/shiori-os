#include "gdt.h"
#include "tss.h"
#include <stdint.h>

extern struct tss_entry tss;

struct gdt_entry gdt[6];
struct gdt_ptr gp;

extern void gdt_flush(uint32_t);

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[num].access = access;
}

void init_gdt() {
    gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
    gp.base = (uint32_t)&gdt;

    // Null segment
    gdt_set_gate(0, 0, 0, 0, 0);

    // Kernel Code (0x08)
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Kernel Data (0x10)
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // User Code (0x18 | 3 = 0x1B)
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // User Data (0x20 | 3 = 0x23)
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // TSS (0x28)
    gdt_set_gate(5, (uint32_t)&tss, sizeof(struct tss_entry), 0x89, 0x40);

    gdt_flush((uint32_t)&gp);
}