#ifndef portio_h
#define portio_h

#include <stdint.h>

uint8_t inportb (uint32_t port);
void outportb (uint32_t port, uint8_t val);
void serial_init ();
void serial_write (char a);
void serial_writeStr (const char * str);

#endif
