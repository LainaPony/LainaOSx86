; gdt_flush.asm
global gdt_flush

gdt_flush:
    ; arg: pointer to gdt_ptr in eax
    mov     eax, [esp + 4]
    lgdt    [eax]

    ; reload segment registers: use selector 0x08 for code, 0x10 for data
    mov     ax, 0x10
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax

    jmp     0x08:.flush_done   ; far jump to reload CS

.flush_done:
    ret
