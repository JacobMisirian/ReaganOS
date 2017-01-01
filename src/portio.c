#include <stdint.h>

#include "portio.h"

uint8_t inportb (uint32_t port) {
	uint8_t ret;
	asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
	return ret;
}

void outportb (uint32_t port, uint8_t val) {
	asm volatile ("outb %%al,%%dx": :"d" (port), "a" (val));
}
