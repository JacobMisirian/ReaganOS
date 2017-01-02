#ifndef gdt_h
#define gdt_h

#define GDT_ENTRIES 5

#include <stddef.h>
#include <stdint.h>


typedef struct gdtEntry {
	unsigned short limitLow;
    unsigned short baseLow;
    unsigned char baseMiddle;
    unsigned char access;
    unsigned char granularity;
    unsigned char baseHigh;
} __attribute__((packed));

typedef struct gdtPtr {
	unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdtEntry gdt [GDT_ENTRIES];
struct gdtPtr gp;

void gdt_init ();

extern void gdt_flush (struct gdtPtr * ptr);

#endif
