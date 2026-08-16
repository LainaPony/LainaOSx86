#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "vga.h"
#include "serial.h"
//this is the kernal, do as you please its your computer
void kmain(void) {
    vga_write("Booting LainaOS x86 1.0 ...\n");

    serial_init();
    serial_write("Serial initialized.\n");

    vga_write("VGA initialized.\n");
    vga_write("Serial initilized.\n");

    while (1) {
        // loops because i'm still testing shit
    }
}
