ENTRY(_start)


SECTIONS
{
	. = 1M;

	.text :
	{
		*(.multiboot)
		*(.text)
	}

	.rodata ALIGN(4K) :
	{
		*(.rodata)
	}

	.data ALIGN(4K) :
	{
		*(.data)
	}

	.bss : {
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
    end = .;
}
