#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/terminal.h>
#include <io/irq.h>
#include <lib/string.h>
#include <mm/heap.h>
#include <arch/device.h>

int main (void *multibootinfo) {
	irq_remap ();
	heap_init ();
	gdt_init ();
	idt_init ();
	irq_init ();
	terminal_init ();
	
	char * str = heap_alloc (50);
	str [0] = 'h';
	str [1] = 'e';
	str [2] = 'y';
	str [3] = 0;
	
	terminal_writeStrLn ("Hello, World! From ReaganOS\n");
	terminal_writeStrLn (strcat ("Hello, ", "world!"));
	int x = 2 - 2;
	terminal_writeStrLn (itoa (5 / x, str, 10));
}
