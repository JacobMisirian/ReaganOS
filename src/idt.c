#include <stddef.h>

#include "idt.h"
#include "string.h"

static void idt_setGate (size_t index, unsigned long base, unsigned short sel, unsigned char flags) {
	idt [index].lowBase = base & 0xFFFF;
	idt [index].highBase = (base >> 16) & 0xFFFF;
	idt [index].sel = sel;
	idt [index].flags = flags;
	idt [index].zero = 0;
}

void idt_init () {
	ip.limit = (sizeof (struct idtEntry) * IDT_ENTRIES) - 1;
	ip.base = &idt;
	
	memset (0, &idt, sizeof(struct idtEntry) * IDT_ENTRIES);
	
	// TODO: set gates
	
	idt_load ();
}
