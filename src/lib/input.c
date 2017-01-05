#include <stdint.h>
#include <arch/device.h>
#include <arch/i386/textscreen.h>
#include <drivers/keyboard.h>
#include <lib/input.h>

device_t * keyboard;

keyEvent_t * readKey () {
	uint8_t key;
	keyboard->read (keyboard, &key, 1, 0);
	return keyboard_scancodeToKeyEvent (key);
}

char * readLine (char * dest) {
	size_t index = 0;
	
	while (1) {
		keyEvent_t * press = readKey ();
		if (press->pressType == KEY_DOWN) {
			textscreen_termWriteChar (press->keyChar);
			if (press->keyChar == 10) {
				dest [index] = 0;
				return dest;
			} else {
				dest [index++] = press->keyChar;
			}
		}
	}
}

void input_init (const char * keyboardName) {
	keyboard = device_getByName ("keyboard");
}
