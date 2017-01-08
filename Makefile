CC = i386-elf-gcc
AS = nasm
AFLAGS = -f elf32
CFLAGS = -c -std=gnu99 -ffreestanding -O0 -Wall -w -g -I ./include
LD = i386-elf-gcc
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -gcc

TARGET = bin/ReaganOS.bin

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c) $(shell find ./src -name "*.c")) $(patsubst %.asm, %.o, $(wildcard *.asm) $(shell find ./src -name "*.asm"))

all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(LD) -o $@ -T linker.ld -ffreestanding -O2 -nostdlib $^ -gcc

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.asm
	$(AS) $(AFLAGS) $^ -o $@
clean:
	rm $(TARGET) $(OBJECTS)

iso:
	cp bin/ReaganOS.bin bin/iso/boot/ReaganOS.bin
	grub-mkrescue -o bin/ReaganOS.iso bin/iso
qemu:
	rm $(TARGET) $(OBJECTS)
	cp bin/ReaganOS.bin bin/iso/boot/ReaganOS.bin
	grub-mkrescue -o bin/ReaganOS.iso bin/iso
	qemu-system-i386 bin/ReaganOS.iso
