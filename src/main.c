#include <arch/device.h>
#include <arch/pit.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/terminal.h>
#include <io/irq.h>
#include <lib/string.h>
#include <mm/heap.h>

int main (void *multibootinfo) {
	irq_remap ();
	heap_init ();
	gdt_init ();
	idt_init ();
	irq_init ();
	terminal_init ();
	pit_init (100);
	
	char * str = heap_alloc (50);
	str [0] = 'h';
	str [1] = 'e';
	str [2] = 'y';
	str [3] = 0;
	
	terminal_writeStrLn ("Hello, World! From ReaganOS\n");
	int x = atoi ("-45");
	terminal_writeStrLn (itoa (x + 2, str, 10));
	int a = 4 / 0;
	pit_sleep (-1);
}
