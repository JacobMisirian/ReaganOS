#ifndef gdt_h
#define gdt_h

#include <stddef.h>

#define GDT_ENTRIES 5

typedef struct gdt_entry {
	unsigned short limitLow;
    unsigned short baseLow;
    unsigned char baseMiddle;
    unsigned char access;
    unsigned char granularity;
    unsigned char baseHigh;
} __attribute__((packed));

typedef struct gdt_ptr {
	unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gp;

void gdt_init ();

extern void gdt_flush ();

#endif
