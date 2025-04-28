global tss_flush
tss_flush:
    mov ax, 0x28 | 0  ; TSS segment (0x28) with RPL 0
    ltr ax
    ret