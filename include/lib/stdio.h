#ifndef stdio_h
#define stdio_h

#include <drivers/keyboard.h>

keyEvent_t * readKey (device_t * keyboard);
char * readLine (char * dest);

#endif
