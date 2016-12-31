#include "gdt.h"
#include "heap.h"
#include "terminal.h"

int main (void *multibootinfo) {
	heap_init ();
	gdt_init ();
	char * str = heap_alloc (10);
	str [0] = 'h';
	str [1] = 'e';
	str [2] = 'y';
	str [3] = 0;
	terminal_init ();
	terminal_writeStr ("Hello, World! From ReaganOS\n");
	terminal_writeStr (str);
	heap_free (str);
	str = heap_alloc (8);
	str [0] = 'h';
	str [1] = 'a';
	str [2] = 'i';
	str [3] = 0;
	terminal_writeStr (str);
}
