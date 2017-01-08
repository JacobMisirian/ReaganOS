#include <stdarg.h>
#include <stdint.h>
#include <arch/device.h>
#include <arch/i386/textscreen.h>
#include <drivers/keyboard.h>
#include <lib/stdio.h>
#include <lib/string.h>

void printf (const char * fstr, ...) {
	va_list args;
	va_start (args, fstr);
	
	int num;
	char * temp [10];
	char * c;
	size_t i;
	for (i = 0; fstr [i] != 0; i++) {
		if (fstr [i] == '%' && fstr [i + 1] != 0) {
			i++;
			switch (fstr [i]) {
				case 'd':
					num = va_arg (args, int);
					textscreen_termWriteStr (itoa (num, temp, 10));
					break;
				case 's':
					c = va_arg (args, char *);
					textscreen_termWriteStr (c);
					break;
				case '%':
					textscreen_termWriteChar ('%');
					break;
			}
		} else {
			textscreen_termWriteChar (fstr [i]);
		}
	}
}

keyEvent_t * readKey (device_t * keyboard) {
	uint8_t key;
	keyboard->read (keyboard, &key, 1, 0);
	return keyboard_scancodeToKeyEvent (key);
}

char * readLine (char * dest) {
	device_t * keyboard = device_getByName ("keyboard");
	size_t index = 0;
	
	while (1) {
		keyEvent_t * press = readKey (keyboard);
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
