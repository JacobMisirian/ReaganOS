#include <stddef.h>

#include <arch/i386/idt.h>
#include <arch/i386/portio.h>
#include <arch/i386/registers.h>
#include <io/irq.h>

static void * irqHandlers [16] = { 0 };

void irq_clearHandler (size_t num) {
	irqHandlers [num] = 0;
}

void irq_setHandler (size_t num, void (* handler)(registers_t * r)) {
	irqHandlers [num] = handler;
}

void irq_init () {
	//irq_remap ();
	asm volatile ("sti");
	idt_setGate (32, (unsigned)irq0, 0x08, 0x8E);
	idt_setGate (33, (unsigned)irq1, 0x08, 0x8E);
	idt_setGate (34, (unsigned)irq2, 0x08, 0x8E);
	idt_setGate (35, (unsigned)irq3, 0x08, 0x8E);
	idt_setGate (36, (unsigned)irq4, 0x08, 0x8E);
	idt_setGate (37, (unsigned)irq5, 0x08, 0x8E);
	idt_setGate (38, (unsigned)irq6, 0x08, 0x8E);
	idt_setGate (39, (unsigned)irq7, 0x08, 0x8E);
	idt_setGate (40, (unsigned)irq8, 0x08, 0x8E);
	idt_setGate (41, (unsigned)irq9, 0x08, 0x8E);
	idt_setGate (42, (unsigned)irq10, 0x08, 0x8E);
	idt_setGate (43, (unsigned)irq11, 0x08, 0x8E);
	idt_setGate (44, (unsigned)irq12, 0x08, 0x8E);
	idt_setGate (45, (unsigned)irq13, 0x08, 0x8E);
	idt_setGate (46, (unsigned)irq14, 0x08, 0x8E);
	idt_setGate (47, (unsigned)irq15, 0x08, 0x8E);
}

void irq_remap () {
    outportb (0x20, 0x11);
    outportb (0xA0, 0x11);
    outportb (0x21, 0x20);
    outportb (0xA1, 0x28);
    outportb (0x21, 0x04);
    outportb (0xA1, 0x02);
    outportb (0x21, 0x01);
    outportb (0xA1, 0x01);
    outportb (0x21, 0x0);
    outportb (0xA1, 0x0);
}

void irq_handler (registers_t * r) {
	void (* handler)(registers_t * r) = irqHandlers [r->num - 32];
	
	if (handler != 0) {
		handler (r);
	}
	
	if (r->num >= 40) {
		outportb (0xA0, 0x20);
	}
	outportb (0x20, 0x20);
}
