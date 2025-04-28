#include "tss.h"
#include <stdint.h>

struct tss_entry tss;

extern void tss_flush();

void init_tss() {
    tss.esp0 = 0x90000;
    tss.ss0 = 0x10; 
    tss_flush();
}