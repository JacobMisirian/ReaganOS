MBALIGN  equ 1<<0
MEMINFO  equ 1<<1
USEGFX   equ 0<<2
FLAGS    equ MBALIGN | MEMINFO
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot

align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    dd 0x00000000 
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000
    dd 0x00000000
    dd 0
    dd 0
    dd 0

section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:

section .text
global _start

_start:
    mov esp, stack_top
    extern main
    push ebx
    call main
    cli
    jmp $
