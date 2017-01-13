#include <stddef.h>
#include <stdint.h>

#include <arch/i386/textscreen.h>
#include <drivers/terminal.h>
#include <mm/heap.h>
#include <lib/string.h>

static void newLine ();

void terminal_flush (struct terminalContext * context) {
	textscreen_reset (context->color);
	uint16_t * buf = (uint16_t *) 0xB8000;
	size_t x;
	size_t y;
	for (y = 0; y < VGA_HEIGHT; y++) {
		for (x = 0; x < VGA_WIDTH; x++) {
			uint16_t entry = context->buffer [y * VGA_WIDTH + x];
			uint8_t c = entry & 0xFF;
			uint8_t col = (entry >> 8);
			textscreen_writeCharAt (c, col, x, y);
		}
	}
}

void terminal_clsColor (struct terminalContext * context, uint8_t color) {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			context->buffer [index] = getVgaEntry (' ', context->color);
		}
	}
}

void terminal_cls (struct terminalContext * context) {
	terminal_clsColor (context, context->color);
}

vgaColor_t terminal_getBColor (struct terminalContext * context) {
	return context->bcolor;
}

vgaColor_t terminal_getFColor (struct terminalContext * context) {
	return context->fcolor;
}

void terminal_init (struct terminalContext * context, vgaColor_t bcol, vgaColor_t fcol) {
	context->row = 0;
	context->column = 0;
	context->buffer = heap_alloc (VGA_WIDTH * VGA_HEIGHT * 2);
	context->bcolor = bcol;
	context->fcolor = fcol;
	context->color = getVgaColor (fcol, bcol);
	terminal_cls (context);
}

static void newLine (struct terminalContext * context) {
	context->column = 0;
	if (++context->row == VGA_HEIGHT) {
		size_t x;
		size_t y;
		uint16_t * temp [VGA_WIDTH];
		for (y = 1; y < VGA_HEIGHT; y++) {
			for (x = 0; x < VGA_WIDTH; x++) {
				temp [x] = context->buffer [y * VGA_WIDTH + x];
			}
			for (x = 0; x < VGA_WIDTH; x++) {
				context->buffer [(y - 1) * VGA_WIDTH + x] = temp [x];
			}
		}
		context->row--;
		for (x = 0; x < VGA_WIDTH; x++) {
			context->buffer [context->row * VGA_WIDTH + x] = getVgaEntry (' ', context->color);
		}
	}
}

void terminal_setBColor (struct terminalContext * context, vgaColor_t color) {
	context->bcolor = color;
	context->color = getVgaColor (context->fcolor, color);
}

void terminal_setFColor (struct terminalContext * context, vgaColor_t color) {
	context->fcolor = color;
	context->color = getVgaColor (context->fcolor, context->bcolor);
}

size_t terminal_write (struct terminalContext * context, char * ptr, size_t bytes, uint64_t offset) {
	size_t i;
	for (i = 0; i < bytes; i++) {
		terminal_writeChar (context, ptr [i + offset]);
	}
	terminal_flush (context);
	return bytes;
}

void terminal_writeCharAt (struct terminalContext * context, char c, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	context->buffer [index] = getVgaEntry (c, context->color);
}

void terminal_writeChar (struct terminalContext * context, char c) {
	switch (c) {
		case '\b':
			if (context->column == 0) {
				context->row--;
				context->column = VGA_WIDTH - 1;
			}		
			context->column--;
			terminal_writeChar (context, ' ');
			context->column--;
			break;
		case '\n':
			newLine (context);
			break;
		case '\t':
			for (size_t i = 0; i < TAB_LENGTH; i++) terminal_writeChar (context, ' ');
			break;
		default:
			terminal_writeCharAt (context, c, context->column, context->row);
			if (++context->column == VGA_WIDTH) {
				newLine (context);
			}
			break;
	}
}
