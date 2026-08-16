global isr_stub_table
global idt_load

extern isr_handler

isr_stub_table:
%assign i 0
%rep 32
    dd isr%+i
%assign i i+1
%endrep

%assign i 0
%rep 32
isr%+i:
    cli
    push dword i
    push dword 0
    jmp isr_common
%assign i i+1
%endrep

isr_common:
    pusha
    call isr_handler
    popa
    add esp, 8
    sti
    iretd

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret
//paaaaaaaaaaaaaaain 
