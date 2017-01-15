#include <stddef.h>
#include <arch/i386/irq.h>
#include <arch/i386/portio.h>
#include <drivers/device.h>
#include <drivers/keyboard.h>

// Standard US Keyboard
static const uint8_t kbdus [128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,				/* Right shift */
	'*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
	'-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
	'+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static uint8_t buffer;
static size_t count = 0;

void keyboard_handler (registers_t * r) {
	uint8_t key = inportb (0x60);
	buffer = key;
	count++;
}

uint8_t keyboard_readKey () {
	size_t cur = count;
	
	while (cur == count) ;
	count = 0;
	return buffer;
}

size_t keyboard_read (struct device_t * self, void * dest, size_t amount, uint64_t offset) {
	size_t i;
	char * cdest = (char *)dest;
	for (i = 0; i < amount; i++) {
		cdest [i + offset] = keyboard_readKey ();
	}
	
	return amount;
}

size_t keyboard_write (struct device_t * self, void  * ptr, size_t bytes, uint64_t offset) {
	// Write to a keyboard? Whaat?
}

size_t keyboard_ioctl (struct device_t * self, int one, int two, int three) {
	
}

device_t * keyboard_init () {
	irq_setHandler (1, keyboard_handler);
	return device_add ("keyboard", keyboard_read, keyboard_write, keyboard_ioctl);
}

keyEvent_t * keyboard_scancodeToKeyEvent (uint8_t key) {
	uint8_t pressType = KEY_DOWN;
	if (key > 128) {
		pressType = KEY_UP;
		key -= 128;
	}
	keyEvent_t * res = 0;
	res->keyChar = kbdus [key];
	res->pressType = pressType;
	
	return res;
}
