#ifndef initrd_h
#define initrd_h

#include <stddef.h>
#include <stdint.h>

#include <kernel/multiboot.h>

typedef struct {
	char name [128];
	char * ptr;
	int64_t len;
	struct initrdFile_t * next;
} initrdFile_t;

char * initrd_getFile (const char * name);
int64_t initrd_getFileLen (const char * name);
void initrd_init (multiboot_info_t * multibootinfo);
char * initrd_listFiles (char * out, char sep);

#endif
