#include <stdarg.h>
#include <stdint.h>
#include <arch/i386/textscreen.h>
#include <drivers/device.h>
#include <drivers/keyboard.h>
#include <lib/stdio.h>
#include <lib/string.h>

static size_t writeStr (char * str, char * part, size_t offset);

void printf (const char * fstr, ...) {
	va_list args;
	va_start (args, fstr);
	
	char str [fstrlen (fstr, args)];
	sprintf (str, fstr, args);
	textscreen_termWriteStr (str);
	va_end (args);
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
			if (press->keyChar == '\b') {
				if (index > 0) {
					textscreen_termWriteChar (press->keyChar);
					dest [index--] = 0;
				}
				continue;
			}
			
			textscreen_termWriteChar (press->keyChar);

			
			if (press->keyChar == '\n') {
				dest [index] = 0;
				return dest;
			} else {
				dest [index++] = press->keyChar;
			}
		}
	}
}

int sprintf (char * str, const char * fstr, va_list args) {
	char * temp [0xF];
	
	size_t strI = 0;
	size_t i;
	
	for (i = 0; fstr [i] != 0; i++) {
		if (fstr [i] == '%' && fstr [i + 1] != 0) {
			i++;
			switch (fstr [i]) {
				case 'b':
					strI += writeStr (str, itoa (va_arg (args, int), temp, 2), strI);
					break;
				case 'c':
					str [strI++] = (uint8_t)va_arg (args, int);
					break;
				case 'd':
					strI += writeStr (str, itoa (va_arg (args, int), temp, 10), strI);
					break;
				case 'o':
					strI += writeStr (str, itoa (va_arg (args, int), temp, 8), strI);
					break;
				case 's':
					strI += writeStr (str, va_arg (args, char *), strI);
					break;
				case 'x':
					strI += writeStr (str, itoa (va_arg (args, int), temp, 16), strI);
					break;
			}
		} else {
			str [strI++] = fstr [i];
		}
	}
	str [strI] = 0;
	return strlen (strI);
}

static size_t writeStr (char * str, char * part, size_t offset) {
	size_t i;
	for (i = offset; part [i - offset] != 0; i++) {
		str [i] = part [i - offset];
	}
	return i - offset;
}
