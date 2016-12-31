#include "terminal.h"
#include "heap.h"

int main (void *multibootinfo) {
	heap_init ();
	terminal_init ();
	terminal_writeStr ("Hello, World! From ReaganOS");
}
