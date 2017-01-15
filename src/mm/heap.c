#include <stddef.h>
#include <stdint.h>

#include <kernel/multiboot.h>
#include <mm/heap.h>
#include <mm/heapBlock.h>

extern unsigned long int end;
static void * nextPtr;
static node_t * freeHead;
static node_t * usedHead;

static void * heap_internalAlloc (size_t bytes);

void heap_init (multiboot_info_t * multibootinfo) {
	nextPtr = *(uint32_t *)(multibootinfo->mods_addr + 4);
	
	freeHead = (node_t *)heap_internalAlloc (sizeof (node_t));
	freeHead->pre = NULL;
	freeHead->next = NULL;
	
	usedHead = (node_t *)heap_internalAlloc (sizeof (node_t));
	usedHead->next = NULL;
	usedHead->pre = NULL;
}

void * heap_alloc (size_t bytes) {
	void * ptr = NULL;
	
	node_t * freeTemp = freeHead;
	while (freeTemp->next != NULL) {
		if (freeTemp->size >= bytes) {
			ptr = freeTemp->ptr;
			freeTemp->next->pre = freeTemp->pre;
			freeTemp->pre->next = freeTemp->next;
			break;
		}
		freeTemp = freeTemp->next;
	}
	
	if (ptr == NULL) {
		ptr = heap_internalAlloc (bytes);
	}
	
	node_t * usedTemp = usedHead;
	while (usedTemp->next != NULL) {
		usedTemp = usedTemp->next;
	}
	usedTemp->next = heap_internalAlloc (sizeof (node_t));
	usedTemp->next->next = NULL;
	usedTemp->next->pre = usedTemp;
	usedTemp->next->ptr = ptr;
	usedTemp->next->size = bytes;
	
	return ptr;
}

int heap_free (void * ptr) {
	node_t * usedTemp = usedHead;
	while (usedTemp->next != NULL) {
		if (usedTemp->ptr == ptr) {
			usedTemp->next->pre = usedTemp->pre;
			usedTemp->pre = usedTemp->next;
			
			node_t * freeTemp = freeHead;
			while (freeTemp->next != NULL) {
				freeTemp = freeTemp->next;
			}
			freeTemp->next = heap_internalAlloc (sizeof (node_t));
			freeTemp->next->next = NULL;
			freeTemp->next->pre = freeTemp;
			freeTemp->next->ptr = ptr;
			freeTemp->next->size = usedTemp->size;
			return 0;
		}
	}
	return -1;
}

static void * heap_internalAlloc (size_t bytes) {
	void * pointer = nextPtr;
	nextPtr += bytes;
	return pointer;
}
