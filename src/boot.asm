# if you don't know what all this does then you're probobly not the kind of person who should be in here fucking with it but if you're the kind of person who does it anyway despite my warning then you're the kind of person who learns the hard way like me and i respect that, good luck brave soul if you choose to ignore my warning.
.code16

.global _start

_start:
	cli #fuck off interupts
	xorw %ax, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw $0x9000, %sp
	lgdt gdt32_descriptor #self explanitory
	movl %cr0, %eax
	orl $1, %eax
	movl %eax, %cr0
	ljmp $0x08, $protected_mode_entry #again self explanitory don't be retarded, read it and you will know with basic brain abilities what this does if you don't then you probobly shouldn't be considered human

.code32 #32 bits my belovid, i want to have sex with 32bits sometimes... but i'm more into milfs nowadays like 64bits
protected_mode_entry:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss #not to be confused with a certain german thing
	movl $0x90000, %esp
	
	movl $0x1000, %edi
	xorl %eax, %eax
	movl $1024, %ecx #hey just a thought why would we boot in 16 bit mode on any cpu built after 1998? seriously? we don't use 16 bit shit anymore and if we do its on a specific machine built specifically to be compatible, my thought is that perhaps its because 16bit real mode is somehow linked to the CIA's hardware malware to try take control over your computer.
	rep stosl
	movl $0x2003, 0x1000
	movl $0x3003, 0x2000
	movl $0x83, 0x3000
	movl $0x100, %eax
	movl %eax, %cr3
	movl %cr4, %eax
	#etc etc give this to eax that to eax fucking eax eax eax..
	movl $0xc0000080, %ecx
	rdmsr
	orl $(1 << 8), %eax
	wrmsr
	movl %cr0, %eax
	orl $(1 << 31), %eax
	movl %eax, %cr0
	lgdt gdt64_descriptor
	ljmp $0x08, $long_mode_entry
	
.code64 #surely you know what this does? what do you THINK it does by now?
long_mode_entry:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movq $0x9000, %rsp
	call kmain 


halt_loop:
	hlt
	jmp halt_loop

gdt32:
    .quad 0x0000000000000000
    .quad 0x00cf9a000000ffff
    .quad 0x00cf92000000ffff
gdt32_descriptor:
    .word . - gdt32 - 1
    .long gdt32
gdt64:
    .quad 0x0000000000000000
    .quad 0x00209a0000000000
    .quad 0x0000920000000000

gdt64_descriptor:
    .word . - gdt64 - 1
    .long gdt64
