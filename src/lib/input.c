#include <stdint.h>
#include <arch/device.h>
#include <arch/i386/terminal.h>
#include <drivers/keyboard.h>
#include <lib/input.h>

char * readLine (char * dest) {
	size_t index = 0;
	device_t * keyboard = device_getByName ("keyboard");
	
	while (1) {
		uint8_t key;
		keyboard->read (keyboard, &key, 1, 0);
		keyEvent_t * press = keyboard_scancodeToKeyEvent (key);
		
		if (press->pressType == KEY_DOWN) {
			terminal_writeChar (press->keyChar);
			if (press->keyChar == 10) {
				dest [index] = 0;
				return dest;
			} else {
				dest [index++] = press->keyChar;
			}
		}
	}
}
