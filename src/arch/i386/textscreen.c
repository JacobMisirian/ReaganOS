#include <stddef.h>
#include <stdint.h>

#include <arch/device.h>
#include <arch/i386/textscreen.h>
#include <lib/string.h>

size_t textscreen_row;
size_t textscreen_column;
uint8_t textscreen_color;
uint16_t * textscreen_buffer;

device_t * ttys [8];
uint8_t tty;

void textscreen_reset (uint8_t color) {
	textscreen_row = 0;
	textscreen_column = 0;
	textscreen_clsColor (color);
}

void textscreen_clsColor (uint8_t color) {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			textscreen_buffer[index] = getVgaEntry (' ', color);
		}
	}
}

void textscreen_cls () {
	textscreen_clsColor (textscreen_color);
}

void textscreen_init () {
	textscreen_row = 0;
	textscreen_column = 0;
	textscreen_color = getVgaColor (VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	textscreen_buffer = (uint16_t*) 0xB8000;
	
	// init background
	textscreen_cls ();
	
	char name [2];
	size_t i;
	for (i = 0; i < 8; i++) {
		ttys [i] = terminal_init (itoa (i, name, 10), textscreen_color);
	}
	tty = 0;
}

void textscreen_writeCharAt (char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	textscreen_buffer[index] = getVgaEntry(c, color);
}

void textscreen_writeChar (char c) {
	switch (c) {
		case '\n':
			textscreen_row++;
			textscreen_column = 0;
			break;
		case '\t':
			for (size_t i = 0; i < TAB_LENGTH; i++) textscreen_writeChar (' ');
			break;
		default:
			textscreen_writeCharAt (c, textscreen_color, textscreen_column, textscreen_row);
			if (++textscreen_column == VGA_WIDTH) {
				textscreen_column = 0;
				if (++textscreen_row == VGA_HEIGHT) {
					textscreen_row = 0;
				}
			}
			break;
	}
}

void textscreen_termWriteChar (char c) {
	ttys [tty]->write (ttys [tty], &c, 1, 0);
}

void textscreen_termWriteStr (const char * str) {
	ttys [tty]->write (ttys [tty], str, strlen (str), 0);
}

static uint8_t newline = '\n';
void textscreen_termWriteStrLn (const char * str) {
	ttys [tty]->write (ttys [tty], str, strlen (str), 0);
	ttys [tty]->write (ttys [tty], &newline, 1, 0);
}

void textscreen_selectTty (uint8_t t) {
	tty = t;
}
