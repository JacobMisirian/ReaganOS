#include <stddef.h>
#include <stdint.h>

#include <kernel/multiboot.h>
#include <io/initrd.h>
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
	
	initrdFile_t * temp = head;
	size_t i;
	for (i = 0; i < count; i++) {
		char name [128];
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
		
		temp = temp->next;
		temp->next = NULL;
	}
}

stream_t * initrd_getFile (const char * name) {
	initrdFile_t * file = getInitrdFile (name);
	if (file == -1)
		return -1;
	return stream_memstreamInit (file->ptr, initrd_getFileLen (name));
}

int64_t initrd_getFileLen (const char * name) {
	initrdFile_t * file = getInitrdFile (name);
	if (file == -1)
		return -1;
	return file->len;
}

char * initrd_listFiles (char * out, char sep) {
	initrdFile_t * temp = head;
	
	size_t outPos = 0;
	
	while (1) {
		size_t i;
		for (i = 0; temp->name [i] != 0; i++) {
			out [outPos++] = temp->name [i];
		}
		out [outPos++] = sep;
		if (temp->next == NULL) {
			return out;
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
