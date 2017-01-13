#ifndef textscreen_h
#define textscreen_h

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define TAB_LENGTH 4

#include <stddef.h>
#include <stdint.h>

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
} vgaColor_t;

uint8_t textscreen_getTty ();
void textscreen_init ();
void textscreen_reset (uint8_t color);
void textscreen_setTty (uint8_t t);
vgaColor_t textscreen_termGetBColor ();
vgaColor_t textscreen_termGetFColor ();
void textscreen_termSetBColor (vgaColor_t col);
void textscreen_termSetFColor (vgaColor_t col);
void textscreen_termWriteChar (char c);
void textscreen_termWriteStr (const char * str);
void textscreen_termWriteStrLn (const char * str);
void textscreen_writeCharAt (char c, uint8_t color, size_t x, size_t y);

static inline uint8_t getVgaColor (vgaColor_t fg, vgaColor_t bg) {
	return fg | bg << 4;
}
 
static inline uint16_t getVgaEntry (unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

#endif
