#include <stdint.h>

#include <stddef.h>
#include <arch/i386/portio.h>

#define PORT 0x3F8

static int is_transmit_empty ();

uint8_t inportb (uint32_t port) {
	uint8_t ret;
	asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
	return ret;
}

void outportb (uint32_t port, uint8_t val) {
	asm volatile ("outb %%al,%%dx": :"d" (port), "a" (val));
}

void serial_init () {
   outportb(PORT + 1, 0x00);
   outportb(PORT + 3, 0x80);
   outportb(PORT + 0, 0x03); 
   outportb(PORT + 1, 0x00);
   outportb(PORT + 3, 0x03);
   outportb(PORT + 2, 0xC7);
   outportb(PORT + 4, 0x0B); 
}
 
void serial_write (char a) {
   while (is_transmit_empty() == 0);
 
   outportb(PORT, a);
}

void serial_writeStr (const char * str) {
	size_t i;
	for (i = 0; str [i] != 0; i++) {
		serial_write (str [i]);
	}
	serial_write ('\n');
}


static int is_transmit_empty () {
   return inportb(PORT + 5) & 0x20;
}
