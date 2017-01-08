#include <arch/device.h>
#include <arch/pit.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/textscreen.h>
#include <drivers/keyboard.h>
#include <drivers/terminal.h>
#include <io/irq.h>
#include <lib/stdio.h>
#include <lib/string.h>
#include <mm/heap.h>

int main (void *multibootinfo) {
	irq_remap ();
	heap_init ();
	gdt_init ();
	idt_init ();
	irq_init ();
	size_t ptr = keyboard_init ();
	textscreen_init ();
	pit_init (100);
	
	char buf [50];
	size_t i = 0;
	while (1) {
		printf ("Type something, and we'll spit it out> ");
		char * str = readLine (buf);
		printf ("%s\n", str);
	}
}
