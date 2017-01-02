#ifndef pit_h
#define pit_h

#include <stdint.h>
#include <arch/i386/registers.h>

void pit_handler (registers_t * r);
void pit_init (uint32_t freq);

#endif
