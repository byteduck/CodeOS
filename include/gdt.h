#ifndef GDT_H
#define GDT_H

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

void gdt_install();

#endif