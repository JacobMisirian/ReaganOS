#ifndef terminal_h
#define terminal_h

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TAB_LENGTH 4

#include <stddef.h>
#include <stdint.h>

void terminal_cls ();
void terminal_clsColor (uint8_t color);
void terminal_init ();
void terminal_writeChar (char c);
void terminal_writeCharAt (char c, uint8_t color, size_t x, size_t y);
void terminal_writeStr (const char * str);
void terminal_writeStrLn (const char * str);

typedef enum {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
        VGA_COLOR_LIGHT_GREY = 7,
        VGA_COLOR_DARK_GREY = 8,
        VGA_COLOR_LIGHT_BLUE = 9,
        VGA_COLOR_LIGHT_GREEN = 10,
        VGA_COLOR_LIGHT_CYAN = 11,
        VGA_COLOR_LIGHT_RED = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN = 14,
        VGA_COLOR_WHITE = 15
} VgaColor_t;

static inline uint8_t getVgaColor (VgaColor_t fg, VgaColor_t bg) {
	return fg | bg << 4;
}
 
static inline uint16_t getVgaEntry (unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

#endif
