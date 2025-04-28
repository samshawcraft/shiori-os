#ifndef H_SYSCALL
#define H_SYSCALL

#define SYSCALL_SYSLOG 103

void register_the_syscall_interrupt(void);
int syscall_dispatcher(int, int, int, int, int, int, int);

#endif