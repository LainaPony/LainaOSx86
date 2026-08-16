#include <stdint.h>
#include "idt.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr   idtp;

extern void idt_load(uint32_t);
extern void isr_stub_table[];   // we will generate 32 ISR stubs because fuck you

static void idt_set_gate(int n, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[n].base_low  = base & 0xFFFF;
    idt[n].sel       = sel;
    idt[n].always0   = 0;
    idt[n].flags     = flags;
    idt[n].base_high = (base >> 16) & 0xFFFF;
}

void idt_init(void)
{
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    // CPU exceptions 0–31
    for (int i = 0; i < 32; i++)
        idt_set_gate(i, (uint32_t)isr_stub_table[i], 0x08, 0x8E);

    idt_load((uint32_t)&idtp);
}
