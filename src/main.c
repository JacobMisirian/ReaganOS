#include <arch/pit.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/irq.h>
#include <arch/i386/portio.h>
#include <arch/i386/textscreen.h>
#include <drivers/keyboard.h>
#include <kernel/debugShell.h>
#include <kernel/multiboot.h>
#include <io/initrd.h>
#include <io/vfs.h>
#include <mm/heap.h>

int main (multiboot_info_t * multibootinfo) {
	serial_init ();
	irq_remap ();
	heap_init (multibootinfo);
	gdt_init ();
	idt_init ();
	irq_init ();
	keyboard_init ();
	textscreen_init ();
	pit_init (100);
	initrd_init (multibootinfo);

	debugShell_start ();
}
