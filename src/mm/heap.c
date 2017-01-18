#include <stddef.h>
#include <stdint.h>

#include <kernel/multiboot.h>
#include <mm/heap.h>
#include <mm/heapBlock.h>
#include <lib/string.h>

extern unsigned long int end;
static void * nextPtr;
static node_t * freeHead;
static node_t * usedHead;

static void * heap_internalAlloc (size_t bytes);

void heap_init (multiboot_info_t * multibootinfo) {
	nextPtr = *(uint32_t *)(multibootinfo->mods_addr + 4);
	
	freeHead = NULL;
	usedHead = NULL;
}

void * heap_alloc (size_t bytes) {
	void * ptr = NULL;
	
	node_t * freeTemp = freeHead;
	while (1) {
		if (freeTemp == NULL) {
			break;
		}
		
		if (freeTemp->size >= bytes) {
			ptr = freeTemp->ptr;
			freeTemp->pre->next = freeTemp->next;
			freeTemp->next->pre = freeTemp->pre;
		}
		freeTemp = freeTemp->next;
	}
	
	if (ptr == NULL) {
		ptr = heap_internalAlloc (bytes);
	}
	
	node_t * usedTemp = usedHead;
	
	while (1) {
		if (usedTemp == NULL) {
			usedHead = heap_internalAlloc (sizeof (node_t));
			usedTemp->next = NULL;
			usedTemp->ptr = ptr;
			usedTemp->size = bytes;
			break;
		}
		if (usedTemp->next == NULL) {
			usedTemp->next = heap_internalAlloc (sizeof (node_t));
			usedTemp->next->next = NULL;
			usedTemp->next->pre = usedTemp;
			usedTemp->next->ptr = ptr;
			usedTemp->next->size = bytes;
			break;
		}
		usedTemp = usedTemp->next;
	}
	return ptr;
}

int heap_free (void * ptr) {
	node_t * usedTemp = usedHead;
	
	while (1) {
		if (usedTemp->ptr == ptr) {
			usedTemp->pre->next = usedTemp->next;
			usedTemp->next->pre = usedTemp->pre;
			node_t * freeTemp = freeHead;
			while (1) {
				if (freeTemp == NULL) {
					freeHead = heap_internalAlloc (sizeof (node_t));
					freeTemp = freeHead;
					freeTemp->next = NULL;
					freeTemp->ptr = ptr;
					freeTemp->size = usedTemp->size;
					return 0;
				}
				if (freeTemp->next == NULL) {
					freeTemp->next = heap_internalAlloc (sizeof (node_t));
					freeTemp->next->next = NULL;
					freeTemp->next->pre = freeTemp;
					freeTemp->next->ptr = ptr;
					freeTemp->next->size = usedTemp->size;
					return 0;
				}
				freeTemp = freeTemp->next;
			}
		}
		if (usedTemp->next == NULL) {
			return -1;
		}
		usedTemp = usedTemp->next;
	}
	return -1;
}

static void * heap_internalAlloc (size_t bytes) {
	void * pointer = nextPtr;
	nextPtr += bytes;
	return pointer;
}
