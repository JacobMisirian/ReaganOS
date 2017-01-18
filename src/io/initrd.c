#include <stddef.h>
#include <stdint.h>

#include <kernel/multiboot.h>
#include <io/initrd.h>
#include <io/vfs.h>
#include <lib/stdio.h>
#include <lib/stream.h>
#include <lib/string.h>
#include <mm/heap.h>

static char * loc;
static int64_t pos;
static int64_t count;

static initrdFile_t * head;

static initrdFile_t * getInitrdFile (const char * name);

void initrd_init (multiboot_info_t * multibootinfo) {
	loc = *(uint32_t *)(multibootinfo->mods_addr);
	pos = sizeof (int64_t);
	count = *loc;
	
	head = heap_alloc (sizeof (initrdFile_t));
	memset (0, head, sizeof (initrdFile_t));
	
	initrdFile_t * temp = head;
	size_t i;
	for (i = 0; i < count; i++) {
		char name [128];
		memset (0, &name, 128); 
		size_t j;
		for (j = 0; loc [pos] != 0; j++) {
			name [j] = loc [pos++];
		}
		pos++;
		int64_t ptr = * (loc + pos);
		pos += sizeof (int64_t);
		int64_t len = * (loc + pos);
		pos += sizeof (int64_t);
		
		strcpy (name, temp->name);
		temp->ptr = loc + ptr;
		temp->len = len;
		temp->next = heap_alloc (sizeof (initrdFile_t));
		memset (0, temp->next, sizeof (initrdFile_t));
		
		temp = temp->next;
	}
	
	filesystem_t * fs = heap_alloc (sizeof (filesystem_t));
	strcpy ("initrd", fs->name);
	strcpy ("/initrd/", fs->root);
	fs->getFileListing = initrd_getFileListing;
	fs->openFile = initrd_openFile;
	fs->next = NULL;
	
	vfs_add (fs);
	
}

stream_t * initrd_openFile (const char * name) {
	initrdFile_t * file = getInitrdFile (name);
	if (file == -1)
		return -1;
	return stream_memstreamInit (file->ptr, file->len);
}

fileEntry_t * initrd_getFileListing (const char * path, fileEntry_t * entry) {
	int file = entry->pos++;
	initrdFile_t * temp = head;
	
	size_t i = 0;
	while (1) {
		if (temp == NULL) {
			entry->pos = -1;
			return entry;
		}
		if (i++ == file) {
			strcpy (temp->name, entry->name);
			return entry;
		}
		temp = temp->next;
	}
}

static initrdFile_t * getInitrdFile (const char * name) {
	initrdFile_t * temp = head;
	
	while (1) {
		if (strcmp (temp->name, name) == 0) {
			return temp;
		}
		if (temp->next == NULL) {
			return -1;
		}
		temp = temp->next;
	}
}
