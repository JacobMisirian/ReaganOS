#include <arch/device.h>
#include <arch/pit.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/terminal.h>
#include <drivers/keyboard.h>
#include <io/irq.h>
#include <lib/input.h>
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
	keyboard_init ();
	char * temp [10];
	
	terminal_writeStrLn ("Hello, World! From ReaganOS");
	
	char * str [50];
	while (1) {
		terminal_writeStr ("Type something, and we'll spit it out > ");
		terminal_writeStrLn (readLine (str));
	}
}
