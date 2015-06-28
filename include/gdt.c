#include "gdt.h"

/* Our GDT, with 3 entries, and finally our special GDT pointer */
struct gdt_entry gdt[3];
struct gdt_ptr gp;

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
extern void gdt_flush();

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran){
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_install(){
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (int)&gdt;

    /* Our null descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);
	
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush();
}