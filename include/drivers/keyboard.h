#ifndef keyboard_h
#define keyboard_h

#include <stddef.h>
#include <stdint.h>

#define KEY_DOWN 0
#define KEY_UP 1

typedef struct {
	uint8_t keyChar;
	uint8_t pressType; // 0 is keyDown, 1 is keyUp
} keyEvent_t;

device_t * keyboard_init ();
keyEvent_t * keyboard_scanCodeToKeyEvent (uint8_t key);

#endif

