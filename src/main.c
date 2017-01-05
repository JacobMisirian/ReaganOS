#include <arch/device.h>
#include <arch/pit.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/textscreen.h>
#include <drivers/keyboard.h>
#include <drivers/terminal.h>
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
	textscreen_init ();
	pit_init (100);
	keyboard_init ();
	input_init ("keyboard");
	
	textscreen_termWriteStrLn ("Hello, World! From ReaganOS");
	
	char * str [50];
	while (1) {
		textscreen_termWriteStr ("Type something, and we'll spit it out > ");
		textscreen_termWriteStrLn (readLine (str));
	}
}
