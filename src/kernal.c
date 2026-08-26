#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
//standard shit
#include "vga.h"
#include "serial.h"
#include "gdt.h"
#include "idt.h"
//better laina header shit
//this is the kernal, do as you please its your computer


extern void shell();
void kmain(void) {
    vga_write("Booting LainaOS x86 1.0 ...\n");

    serial_init();
    serial_write("Serial initialized.\n");

    gdt_init();
    vga_write("GDT initialized.\n");

    vga_write("VGA initialized.\n");
    vga_write("Serial initilized.\n");
    shell(); //if this shit works first try somehow i will be shocked
    while (1) {
        // loops because i'm still testing shit
    }
}
