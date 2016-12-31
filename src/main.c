#include "terminal.h"
#include "heap.h"

int main (void *multibootinfo) {
	heap_init ();
	char * str = heap_alloc (10);
	str [0] = 'h';
	str [1] = 'e';
	str [2] = 'y';
	str [3] = 0;
	terminal_init ();
	terminal_writeStr ("Hello, World! From ReaganOS\n");
	terminal_writeStr (str);
	terminal_writeStr (str);
}
