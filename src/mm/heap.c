#include <stddef.h>
#include <stdint.h>

#include <kernel/multiboot.h>
#include <mm/heap.h>
#include <mm/heapBlock.h>

extern unsigned long int end;

static void * nextPtr;

static node_t * freeHead;
static node_t * usedHead;

static void * heap_internalAlloc (size_t bytes) {
	void * pointer = nextPtr;
	nextPtr += bytes;
	return pointer;
}

void heap_init (multiboot_info_t * multibootinfo) {
	nextPtr = *(uint32_t *)(multibootinfo->mods_addr + 4);
	
	freeHead = NULL;
	usedHead = NULL;
}

size_t heap_free (void * ptr) {
}

void * heap_alloc (size_t bytes) {
	return heap_internalAlloc (bytes);
	if (freeHead == NULL) {
		freeHead = (node_t *)heap_internalAlloc (sizeof (node_t));
		freeHead->ptr = NULL;
		freeHead->size = NULL;
		freeHead->next = NULL;
	}
	
	void * ptr = NULL;
	
	node_t * temp = freeHead;
	
	while (temp->next != NULL) {
		if (temp->size >= bytes) {
			ptr = temp->ptr;
			break;
		}
		temp = temp->next;
	}
	
	if (ptr == NULL) {
		ptr = heap_internalAlloc (bytes);
	}
	
	temp = usedHead;
	
	while (temp->next != NULL) {
		temp = temp->next;
	}
	
	node_t * block = (node_t *) heap_internalAlloc (sizeof (node_t));
	block->ptr = ptr;
	block->size = bytes;
	block->next = NULL;
	temp->next = block;
	
	return ptr;
}
