#include "syscall.h"
#include "kernel/syscalls/packed.h"
#include "kernel/lib/include/stdio.h"
#include "idt.h"
#include "isr.h"

extern void syscall_handler_asm();

void register_the_syscall_interrupt(){
  register_an_interrupt(0x80, (unsigned int) syscall_handler_asm, CODE_DESC_SELECTOR, IDT_USER_GATE);
}

// Can refer to Linux Syscall Table https://gist.github.com/GabriOliv/a9411fa771a1e5d94105cb05cbaebd21
int syscall_dispatcher(int eax, int ebx, int ecx, int edx, int esi, int edi, int ebp) {
  printf("Syscall %d is called with (%d, %d, %d, %d, %d, %d).\n", eax, ebx, ecx, edx, esi, edi, ebp);
  switch(eax){
  case SYSCALL_SYSLOG:
    int type = ebx;
    char *msg = (char *)ecx;
    int len = edx;
    syslog(type, msg, len);
    break;
  default:
  }
  return -1;
}