BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti

    mov ah, 0x00
    mov al, 0x03
    int 0x10

    mov si, banner
    call print_string

main_loop:
    mov si, prompt
    call print_string
    mov di, input_buf
    call read_line
    mov si, input_buf
    lodsb
    cmp al, 'D'
    je cmd_dump
    cmp al, 'M'
    je cmd_modify
    cmp al, 'H'
    je cmd_help
    cmp al, 'R'
    je cmd_reboot
    jmp main_loop

cmd_help:
    mov si, help_text
    call print_string
    jmp main_loop

cmd_reboot:
    mov ax, 0x40
    mov ds, ax
    mov word [0x0072], 0x1234
    jmp 0xFFFF:0x0000

cmd_dump:
    mov si, input_buf
    inc si
    call parse_seg_off
    mov ds, ax
    mov si, dump_header
    call print_string
    mov cx, 16
dump_loop:
    mov al, [bx]
    call print_hex2
    mov al, ' '
    call print_char
    inc bx
    loop dump_loop
    mov al, 0x0D
    call print_char
    mov al, 0x0A
    call print_char
    mov ds, 0
    jmp main_loop

cmd_modify:
    mov si, input_buf
    inc si
    call parse_seg_off
    mov ds, ax
    mov si, modify_msg
    call print_string
    mov di, input_buf2
    call read_line
    mov si, input_buf2
    call parse_hex2
    mov [bx], al
    mov si, ok_msg
    call print_string
    mov ds, 0
    jmp main_loop

print_string:
    push ax
    push si
.ps_loop:
    lodsb
    test al, al
    jz .ps_done
    call print_char
    jmp .ps_loop
.ps_done:
    pop si
    pop ax
    ret

print_char:
    push ax
    push bx
    push cx
    push dx
    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x07
    int 0x10
    pop dx
    pop cx
    pop bx
    pop ax
    ret

read_line:
    push ax
    push di
.rl_loop:
    mov ah, 0x00
    int 0x16
    cmp al, 0x0D
    je .rl_done
    call print_char
    stosb
    jmp .rl_loop
.rl_done:
    mov al, 0
    stosb
    mov al, 0x0D
    call print_char
    mov al, 0x0A
    call print_char
    pop di
    pop ax
    ret

parse_hex_digit:
    cmp al, '0'
    jb .err
    cmp al, '9'
    jbe .num
    cmp al, 'A'
    jb .err
    cmp al, 'F'
    jbe .upper
    cmp al, 'a'
    jb .err
    cmp al, 'f'
    jbe .lower
.err:
    stc
    ret
.num:
    sub al, '0'
    clc
    ret
.upper:
    sub al, 'A'
    add al, 10
    clc
    ret
.lower:
    sub al, 'a'
    add al, 10
    clc
    ret

parse_hex2:
    push bx
    lodsb
    call parse_hex_digit
    jc .ph2_err
    mov bl, al
    lodsb
    call parse_hex_digit
    jc .ph2_err
    shl bl, 4
    or al, bl
    jmp .ph2_done
.ph2_err:
    xor al, al
.ph2_done:
    pop bx
    ret

parse_hex4:
    xor dx, dx
    mov cx, 4
.ph4_loop:
    lodsb
    call parse_hex_digit
    jc .ph4_err
    shl dx, 4
    add dl, al
    loop .ph4_loop
    mov ax, dx
    ret
.ph4_err:
    xor ax, ax
    ret

parse_seg_off:
    call parse_hex4
    mov dx, ax
    lodsb
    lodsb
    call parse_hex4
    mov bx, ax
    mov ax, dx
    ret

print_hex2:
    push ax
    push bx
    mov bl, al
    shr bl, 4
    call print_hex_nibble
    mov bl, al
    and bl, 0x0F
    call print_hex_nibble
    pop bx
    pop ax
    ret

print_hex_nibble:
    push ax
    mov al, bl
    cmp al, 9
    jbe .digit
    add al, 'A' - 10
    jmp .out
.digit:
    add al, '0'
.out:
    call print_char
    pop ax
    ret

banner:
    db 0x0D,0x0A
    db "LainaMon",0x0D,0x0A,0
prompt:
    db "> ",0
help_text:
    db "Dssss:oooo Mssss:oooo H R",0x0D,0x0A,0
dump_header:
    db "Dump",0x0D,0x0A,0
modify_msg:
    db "New:",0
ok_msg:
    db "OK",0x0D,0x0A,0

input_buf:   times 32 db 0
input_buf2:  times 4  db 0

times 510-($-$$) db 0
dw 0xAA55
;Надоело писать код на ассемблере, но он нужен на случай, если грёбаное ЦРУ взломает мой компьютер, эти грёбаные тупые суки-идиоты.