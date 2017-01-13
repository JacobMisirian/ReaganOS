#ifndef terminal_h
#define terminal_h

#include <stddef.h>
#include <stdint.h>

struct terminalContext {
	size_t row;
	size_t column;
	uint8_t color;
	uint16_t * buffer;
};

#endif
