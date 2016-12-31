#include <stddef.h>
#include <stdint.h>

#include "terminal.h"



size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_cls () {
	terminal_clsColor (terminal_color);
}

void terminal_clsColor (uint8_t color) {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = getVgaEntry (' ', color);
		}
	}
}

void terminal_init () {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = getVgaColor (VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	
	// init background
	terminal_cls ();
}

void terminal_writeCharAt (char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = getVgaEntry(c, color);
}

void terminal_writeChar (char c) {
	switch (c) {
		case '\n':
			terminal_row++;
			terminal_column = 0;
			break;
		case '\t':
			for (size_t i = 0; i < TAB_LENGTH; i++) terminal_writeChar (' ');
			break;
		default:
			terminal_writeCharAt (c, terminal_color, terminal_column, terminal_row);
			if (++terminal_column == VGA_WIDTH) {
				terminal_column = 0;
				if (++terminal_row == VGA_HEIGHT) {
					terminal_row = 0;
				}
			}
			break;
	}
}

void terminal_writeStr(const char * str) {
	size_t pos = 0;
	while (str [pos] != 0)
		terminal_writeChar (str [pos++]);
}

void terminal_writeStrLn(const char * str) {
	terminal_writeStr (str);
	terminal_writeChar ('\n');
}
