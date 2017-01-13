#ifndef terminal_h
#define terminal_h

#include <stddef.h>
#include <stdint.h>

struct terminalContext {
	size_t row;
	size_t column;
	vgaColor_t bcolor;
	vgaColor_t fcolor;
	uint8_t color;
	uint16_t * buffer;
};

void terminal_flush (struct terminalContext * context);
void terminal_cls (struct terminalContext * context);
vgaColor_t terminal_getBColor (struct terminalContext * context);
vgaColor_t terminal_getFColor (struct terminalContext * context);
void terminal_setBColor (struct terminalContext * context, vgaColor_t color);
void terminal_setFColor (struct terminalContext * context, vgaColor_t color);

#endif
