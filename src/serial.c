#include <stdint.h>
//serial driver incase you somehow lack a screen yet have 64 bit computer ,very rare situation but you can use the com port i serpose,but maybe consider a monitor
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void serial_init() {
    outb(0x3F8 + 1, 0x00);
    outb(0x3F8 + 3, 0x80);
    outb(0x3F8 + 0, 0x03);
    outb(0x3F8 + 1, 0x00);
    outb(0x3F8 + 3, 0x03);
    outb(0x3F8 + 2, 0xC7);
    outb(0x3F8 + 4, 0x0B);
}

int serial_ready() {
    return inb(0x3F8 + 5) & 0x20;
}

void serial_put(char c) {
    while (!serial_ready());
    outb(0x3F8, c);
}

void serial_write(const char* s) {
    while (*s) serial_put(*s++);
}
