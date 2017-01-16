#ifndef initrd_h
#define initrd_h

#include <stddef.h>
#include <stdint.h>

#include <io/vfs.h>
#include <kernel/multiboot.h>
#include <lib/stream.h>

typedef struct {
	char name [128];
	char * ptr;
	int64_t len;
	struct initrdFile_t * next;
} initrdFile_t;

void initrd_init (multiboot_info_t * multibootinfo);
stream_t * initrd_openFile (const char * name);
fileEntry_t * initrd_getFileListing (const char * path);

#endif
