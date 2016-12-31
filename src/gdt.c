#include <stddef.h>

#include "gdt.h"

static void gdt_setGate (size_t index, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
	gdt [index].baseLow = base & 0xFFFF;
	gdt [index].baseMiddle = (base >> 16) & 0xFF;
	gdt [index].baseHigh = (base >> 24) & 0xFF;
	
	gdt [index].limitLow = limit & 0xFFFF;
	gdt [index].granularity = (limit >> 16) & 0x0F;
	gdt [index].granularity |= gran & 0xF0;
	
	gdt [index].access = access;
}

void gdt_init () {
	gp.limit = (sizeof (struct gdtEntry) * GDT_ENTRIES) - 1;
	gp.base = &gdt;
	
	gdt_setGate (0, 0, 0, 0, 0);
	gdt_setGate (1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_setGate (2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_setGate (3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_setGate (4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
}
