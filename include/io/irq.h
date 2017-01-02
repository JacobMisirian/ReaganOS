#ifndef irq_h
#define irq_h

#include <stddef.h>
#include <arch/i386/registers.h>

void irq_clearHandler (size_t num);
void irq_setHandler (size_t num, void (* handler)(registers_t * r));
void irq_init ();
void irq_remap ();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif
