#include <stddef.h>
#include <stdint.h>

#include <arch/i386/textscreen.h>
#include <drivers/terminal.h>
#include <lib/stdio.h>
#include <lib/string.h>
#include <mm/heap.h>

static size_t textscreen_row;
static size_t textscreen_column;
static uint8_t textscreen_color;
static uint16_t * textscreen_buffer;

static struct terminalContext * ttys [8];
static uint8_t tty;

void textscreen_cls () {
	textscreen_clsColor (textscreen_color);
}

void textscreen_clsColor (uint8_t color) {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			textscreen_buffer[index] = getVgaEntry (' ', color);
		}
	}
}

uint8_t textscreen_getTty () {
	return tty;
}

void textscreen_init () {
	textscreen_row = 0;
	textscreen_column = 0;
	textscreen_color = 0;
	textscreen_buffer = (uint16_t *) 0xB8000;
	
	// init background
	textscreen_cls ();
	
	size_t i;
	for (i = 0; i < 8; i++) {
		struct terminalContext * context = heap_alloc (sizeof (struct terminalContext));
		terminal_init (context, VGA_COLOR_BLACK, VGA_COLOR_RED);
		ttys [i] = context;
	}
	tty = 0;
}

void textscreen_reset (uint8_t color) {
	textscreen_row = 0;
	textscreen_column = 0;
	textscreen_clsColor (color);
}

vgaColor_t textscreen_termGetBColor () {
	return terminal_getBColor (ttys [tty]);
}

vgaColor_t textscreen_termGetFColor () {
	return terminal_getFColor (ttys [tty]);
}

void textscreen_termSetBColor (vgaColor_t col) {
	terminal_setBColor (ttys [tty], col);
}

void textscreen_termSetFColor (vgaColor_t col) {
	terminal_setFColor (ttys [tty], col);
}

void textscreen_setTty (uint8_t t) {
	tty = t;
}

void textscreen_termWriteChar (char c) {
	terminal_write (ttys [tty], &c, 1, 0);
}

void textscreen_termWriteStr (const char * str) {
	terminal_write (ttys [tty], str, strlen (str), 0);
}

static const uint8_t newline = '\n';
void textscreen_termWriteStrLn (const char * str) {
	terminal_write (ttys [tty], str, strlen (str), 0);
	terminal_write (ttys [tty], &newline, 1, 0);
}

void textscreen_writeCharAt (char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	textscreen_buffer[index] = getVgaEntry(c, color);
}
