#ifndef idt_h
#define idt_h

#define IDT_ENTRIES 256

#include <stddef.h>

typedef struct idtEntry {
	unsigned short lowBase;
    unsigned short highBase;
    unsigned short sel;
    unsigned char flags;
    unsigned char zero;
} __attribute__((packed));

typedef struct idtPtr {
	unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idtEntry idt [IDT_ENTRIES];
struct idtPtr ip;

extern void idt_load ();

#endif
