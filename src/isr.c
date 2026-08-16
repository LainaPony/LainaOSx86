#include <stdint.h>
#include "vga.h"
#include "serial.h"

const char* exception_names[] = {
    "Divide-by-zero",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Bound Range",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating Point",
    "Alignment Check",
    "Machine Check",
    "SIMD FP",
    "Virtualization",
    "Control Protection",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(uint32_t int_no)
{
    serial_write("[EXCEPTION] ");
    serial_write(exception_names[int_no]);
    serial_write("\n");

    vga_write("[EXCEPTION] ");
    vga_write(exception_names[int_no]);
    vga_write("\n");

    while (1);
}
//you know you're right
