#include "serial.h" //directly took code from other port pleace note this isn't checked for x86 as of uploading it.
#include "vga.h"
#include <stdbool.h>

#define CMD_BUF 128

void shell()
{
    char buf[CMD_BUF];
    int pos = 0;

    vga_print("CMD> ");

    while (1) {
        char c = serial_read();   // blocking read from COM1

        if (c == '\r' || c == '\n') {
            buf[pos] = 0;
            vga_print("\n");

            run_command(buf);

            pos = 0;
            vga_print("LainaShell> ");
        } else {
            if (pos < CMD_BUF - 1) {
                buf[pos++] = c;
                vga_putc(c);
            }
        }
    }
}
