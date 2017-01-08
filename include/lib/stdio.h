#ifndef stdio_h
#define stdio_h

#include <stdarg.h>
#include <drivers/keyboard.h>

void printf (const char * fstr, ...);
keyEvent_t * readKey (device_t * keyboard);
char * readLine (char * dest);
sprintf (char * str, const char * fstr, va_list args);

#endif
