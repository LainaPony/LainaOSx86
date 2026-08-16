#include <stdint.h>

static uint16_t* const VGA = (uint16_t*)0xB8000;
static int cursor = 0;

void vga_put(char c) {
    VGA[cursor++] = (uint16_t)c | (0x0F << 8);
}

void vga_write(const char* s) {
    while (*s) vga_put(*s++);
}
