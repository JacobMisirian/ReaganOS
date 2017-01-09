#include <arch/pit.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/textscreen.h>
#include <drivers/keyboard.h>
#include <io/irq.h>
#include <kernel/debugShell.h>
#include <mm/heap.h>

int main (void *multibootinfo) {
	irq_remap ();
	heap_init ();
	gdt_init ();
	idt_init ();
	irq_init ();
	keyboard_init ();
	textscreen_init ();
	pit_init (100);

	debugShell_start ();
}
