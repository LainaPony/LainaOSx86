// global descriptor table
#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  gran;
    uint8_t  base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct gdt_entry gdt[3];
static struct gdt_ptr   gp;

extern void gdt_flush(uint32_t);
//flush that shit away 
static void gdt_set_entry(int idx, uint32_t base, uint32_t limit,
                          uint8_t access, uint8_t gran)
{
    gdt[idx].limit_low = (uint16_t)(limit & 0xFFFF);
    gdt[idx].base_low  = (uint16_t)(base & 0xFFFF);
    gdt[idx].base_mid  = (uint8_t)((base >> 16) & 0xFF);
    gdt[idx].access    = access;
    gdt[idx].gran      = (uint8_t)(((limit >> 16) & 0x0F) | (gran & 0xF0));
    gdt[idx].base_high = (uint8_t)((base >> 24) & 0xFF);
}

void gdt_init(void)
{
    gp.limit = sizeof(gdt) - 1;
    gp.base  = (uint32_t)&gdt;

    // null descriptor
    gdt_set_entry(0, 0, 0, 0, 0);

    // kernel code: base=0, limit=0xFFFFF, access=0x9A, gran=0xCF
    gdt_set_entry(1, 0, 0x000FFFFF, 0x9A, 0xCF);

    // kernel data: base=0, limit=0xFFFFF, access=0x92, gran=0xCF
    gdt_set_entry(2, 0, 0x000FFFFF, 0x92, 0xCF);

    gdt_flush((uint32_t)&gp);
}


