#include "gdt.h"
#include "heap.h"
#include "idt.h"
#include "string.h"
#include "terminal.h"

int main (void *multibootinfo) {
	heap_init ();
	idt_init ();
	gdt_init ();
	terminal_init ();
	
	char * str = heap_alloc (50);
	str [0] = 'h';
	str [1] = 'e';
	str [2] = 'y';
	str [3] = 0;
	
	terminal_writeStrLn ("Hello, World! From ReaganOS\n");
	terminal_writeStrLn (strcat ("Hello, ", "world!"));
	terminal_writeStrLn (itoa (5 / 0, str, 0));
}
