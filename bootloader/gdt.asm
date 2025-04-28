[bits 16]
gdt_start:
    gdt_null:
        dd 0x0
        dd 0x0

    ; Kernel Code Segment (DPL 0)
    gdt_code:
        dw 0xFFFF       ; Limit (0-15)
        dw 0x0000       ; Base (0-15)
        db 0x00         ; Base (16-23)
        db 10011010b    ; Access Byte (Present, DPL 0, Code, Exec/Read)
        db 11001111b    ; Flags (4KB Granularity, 32-bit) + Limit (16-19)
        db 0x00         ; Base (24-31)

    ; Kernel Data Segment (DPL 0)
    gdt_data:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 10010010b    ; Access Byte (Present, DPL 0, Data, Read/Write)
        db 11001111b
        db 0x00

    ; User Code Segment (DPL 3)
    gdt_user_code:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 11111010b    ; Access Byte (Present, DPL 3, Code, Exec/Read)
        db 11001111b
        db 0x00

    ; User Data Segment (DPL 3)
    gdt_user_data:
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 11110010b    ; Access Byte (Present, DPL 3, Data, Read/Write)
        db 11001111b
        db 0x00

    ; TSS Segment (Add placeholder)
    gdt_tss:
        dw 0x0000       ; Limit (0-15)
        dw 0x0000       ; Base (0-15)
        db 0x00         ; Base (16-23)
        db 10001001b    ; Access Byte (Present, DPL 0, 32-bit TSS)
        db 00000000b    ; Flags + Limit (16-19)
        db 0x00         ; Base (24-31)
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start  ; 0x08
DATA_SEG equ gdt_data - gdt_start  ; 0x10
