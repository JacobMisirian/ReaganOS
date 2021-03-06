#include <stdint.h>
#include <stdint.h>
#include <arch/pit.h>
#include <arch/i386/irq.h>
#include <arch/i386/portio.h>
#include <arch/i386/registers.h>
#include <lib/stdio.h>

static size_t ticks = 0;
static size_t frequency;

size_t pit_getTicks () {
	return ticks;
}

void pit_handler (registers_t * r) {
	ticks++;
}

void pit_init (uint32_t freq) {
	frequency = freq;
	uint32_t div = 1193180 / freq;
	
	outportb (0x43, 0x36);
	outportb (0x40, div & 0xFF);
	outportb (0x40, div >> 8);
	
	irq_setHandler (0, pit_handler);
}

void pit_sleep (size_t num) {
	size_t end = ticks + num;
	
	while (ticks < end) ;
}

void pit_sleepSecs (size_t secs) {
	pit_sleep (secs * frequency);
}
