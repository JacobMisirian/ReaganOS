#include <stddef.h>
#include <arch/i386/irq.h>
#include <arch/i386/portio.h>
#include <drivers/device.h>
#include <drivers/keyboard.h>

// Standard US Keyboard
static const uint8_t kbdus [128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,				/* Right shift */
	'*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
	'-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
	'+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

static const uint8_t kbdus_shift [128] = {
  0,                        //               0
  27,                       // ESC ^[        1
  '!', '@', '#', '$', '%',  // Numbers       2 -  6
  '^', '&', '*', '(', ')',  // Numbers       7 - 11
  '_', '+', '\b', '\t',     //              12 - 15
  'Q', 'W', 'E', 'R', 'T',  // Chars        16 - 20
  'Y', 'U', 'I', 'O', 'P',  // Chars        21 - 25
  '{', '}', '\n',           //              26 - 28
  0,                        // Control      29
  'A', 'S', 'D', 'F', 'G',  // Chars        30 - 34
  'H', 'J', 'K', 'L',       // Chars        35 - 38
  ':', '\"', '`',           //              39 - 41
  0,                        // Lshift       42
  '|',                     //              43
  'Z', 'X', 'C', 'V', 'B',  // Chars        44 - 48
  'N', 'M',                 // Chars        49 - 50
  '<', '>', '?',            //              51 - 53
  0,                        // Rshift       54
  '*',                      //              55
  0,                        // Alt          56
  ' ',                      // Space        57
  0,                        // Caps lock    58
  0, 0, 0, 0, 0,            // F1 - F5      59 - 63
  0, 0, 0, 0, 0,            // F6 - F10     64 - 68
  0,                        // Num lock     69
  0,                        // Scroll lock  70
  0,                        // Home key     71
  0,                        // Arrow up     72
  0,                        // Page up      73
  '-',                      // Num minus    74
  0,                        // Arrow left   75
  0,                        //              76
  0,                        // Arrow right  77
  '+',                      // Num plus     78
  0,                        // End          79
  0,                        // Arrow down   80
  0,                        // Page down    81
  0,                        // Insert       82
  0,                        // Delete       83
  0, 0, 0,                  //              84 - 87
  0, 0,                     // F11 - F12    88 - 89
  0,                        //              90
};

static uint8_t buffer;
static size_t count = 0;
static size_t shiftPressed = 0;

void keyboard_handler (registers_t * r) {
	uint8_t key = inportb (0x60);
	if (key == 42 || key == 54) {
		shiftPressed = 1;
	} else if (key == 128 + 42 || key == 128 + 54) {
		shiftPressed = 0;
	}
	buffer = key;
	count++;
}

uint8_t keyboard_readKey () {
	size_t cur = count;
	while (cur == count) ;
	count = 0;
	return buffer;
}

size_t keyboard_read (struct device_t * self, void * dest, size_t amount, uint64_t offset) {
	size_t i;
	char * cdest = (char *)dest;
	for (i = 0; i < amount; i++) {
		cdest [i + offset] = keyboard_readKey ();
	}
	
	return amount;
}

size_t keyboard_write (struct device_t * self, void  * ptr, size_t bytes, uint64_t offset) {
	// Write to a keyboard? Whaat?
}

size_t keyboard_ioctl (struct device_t * self, int one, int two, int three) {
	
}

device_t * keyboard_init () {
	irq_setHandler (1, keyboard_handler);
	return device_add ("keyboard", keyboard_read, keyboard_write, keyboard_ioctl);
}

keyEvent_t * keyboard_scancodeToKeyEvent (uint8_t key) {
	uint8_t pressType = KEY_DOWN;
	if (key > 128) {
		pressType = KEY_UP;
		key -= 128;
	}
	keyEvent_t * res = 0;
	res->keyChar = kbdus [key];
	res->keyCharShift = res->keyChar;
	res->pressType = pressType;
	res->scanCode = key;
	
	if (shiftPressed == 1) {
		res->keyCharShift = kbdus_shift [key];
	}
	
	return res;
}
