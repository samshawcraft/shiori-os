[bits 32]
global syscall_handler_asm

extern syscall_dispatcher

syscall_handler_asm:
    cli  ; Clear interrupts during critical section
    
    ; Save user data segments
    push ds
    push es
    push fs
    push gs
    
    ; Load kernel data segments (0x10 = kernel data segment)
    ;mov ax, 0x10
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax
    
    ; Create stack frame
    push ebp
    mov ebp, esp
    
    ; Push arguments (reverse order)
    push ebp  ; arg6
    push edi  ; arg5
    push esi  ; arg4
    push edx  ; arg3
    push ecx  ; arg2
    push ebx  ; arg1
    push eax  ; syscall number
    
    call syscall_dispatcher
    
    ; Cleanup stack
    add esp, 28  ; 7 arguments * 4 bytes
    
    ; Restore user segments
    pop ebp
    pop gs
    pop fs
    pop es
    pop ds
    
    sti  ; Re-enable interrupts
    iretd  ; Return to user mode