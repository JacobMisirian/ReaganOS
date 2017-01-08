#include <stddef.h>
#include <stdint.h>

#include <arch/i386/idt.h>
#include <arch/i386/registers.h>
#include <lib/string.h>

static char * exceptionMessages [] = {
	"Divide by zero",
	"Debug",
	"Non maskable interrupt",
	"Breakpoint",
	"Into detected overflow",
	"Out of bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",
	"Coprocessor fault",
	"Alignment check",
	"Machine check",
	"Unknown"
};

void idt_setGate (size_t index, unsigned long base, unsigned short sel, unsigned char flags) {
	idt [index].lowBase = base & 0xFFFF;
	idt [index].highBase = (base >> 16) & 0xFFFF;
	idt [index].sel = sel;
	idt [index].flags = flags;
	idt [index].zero = 0;
}

void idt_init () {
	struct idtPtr iPtr;
	iPtr.limit = (sizeof (struct idtEntry) * IDT_ENTRIES) - 1;
	iPtr.base = &idt;
	
	memset (0, &idt, sizeof(struct idtEntry) * IDT_ENTRIES);
	
	idt_setGate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_setGate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_setGate(2, (unsigned)isr2, 0x08, 0x8E);
    idt_setGate(3, (unsigned)isr3, 0x08, 0x8E);
    idt_setGate(4, (unsigned)isr4, 0x08, 0x8E);
    idt_setGate(5, (unsigned)isr5, 0x08, 0x8E);
    idt_setGate(6, (unsigned)isr6, 0x08, 0x8E);
    idt_setGate(7, (unsigned)isr7, 0x08, 0x8E);
    idt_setGate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_setGate(9, (unsigned)isr9, 0x08, 0x8E);
    idt_setGate(10, (unsigned)isr10, 0x08, 0x8E);
    idt_setGate(11, (unsigned)isr11, 0x08, 0x8E);
    idt_setGate(12, (unsigned)isr12, 0x08, 0x8E);
    idt_setGate(13, (unsigned)isr13, 0x08, 0x8E);
    idt_setGate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_setGate(15, (unsigned)isr15, 0x08, 0x8E);
    idt_setGate(16, (unsigned)isr16, 0x08, 0x8E);
    idt_setGate(17, (unsigned)isr17, 0x08, 0x8E);
    idt_setGate(18, (unsigned)isr18, 0x08, 0x8E);
    idt_setGate(19, (unsigned)isr19, 0x08, 0x8E);
    idt_setGate(20, (unsigned)isr20, 0x08, 0x8E);
    idt_setGate(21, (unsigned)isr21, 0x08, 0x8E);
    idt_setGate(22, (unsigned)isr22, 0x08, 0x8E);
    idt_setGate(23, (unsigned)isr23, 0x08, 0x8E);
    idt_setGate(24, (unsigned)isr24, 0x08, 0x8E);
    idt_setGate(25, (unsigned)isr25, 0x08, 0x8E);
    idt_setGate(26, (unsigned)isr26, 0x08, 0x8E);
    idt_setGate(27, (unsigned)isr27, 0x08, 0x8E);
    idt_setGate(28, (unsigned)isr28, 0x08, 0x8E);
    idt_setGate(29, (unsigned)isr29, 0x08, 0x8E);
    idt_setGate(30, (unsigned)isr30, 0x08, 0x8E);
    idt_setGate(31, (unsigned)isr31, 0x08, 0x8E);
	
	asm volatile ("lidt (%0)" : : "p" (&iPtr));
}

void fault_handler(registers_t * r) {
	if (r->num < 32) {
		textscreen_termWriteStr ("Kernel Panic! Exception type: ");
		textscreen_termWriteStrLn (exceptionMessages [r->num]);
	}
	while (1);
}
