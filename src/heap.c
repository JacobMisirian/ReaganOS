#include <stddef.h>
#include <stdint.h>

#include "heap.h"
#include "heapBlock.h"

unsigned long int end;

static node_t * nodeAt (node_t * head, size_t index) {
	node_t * curNode = head;
	
	size_t i;
	for (i = 0; i < index; i++) {
		curNode = curNode->next;
	}
	
	return curNode;
}

void * heap_internalAlloc (size_t bytes) {
	void * pointer = nextPtr;
	nextPtr += bytes;
	return pointer;
}

static void addNode (node_t * head, void * ptr, size_t size) {
	node_t * lastBlock = nodeAt (head, head->len - 1);
	
	lastBlock->next = heap_internalAlloc (sizeof (node_t));
	lastBlock->next->ptr = ptr;
	lastBlock->next->size = size;
	
	head->len += 1;
}

void heap_init () {
	nextPtr = &end;
	
	freeHead = heap_internalAlloc (sizeof (node_t));
	usedHead = heap_internalAlloc (sizeof (node_t));
	
	freeHead->len = 1;
	usedHead->len = 1;
}

void size_t heap_free (void * ptr) {
	node_t * curNode = usedHead;
	
	size_t i;
	for (i = 0; i < usedHead->len; i++) {
		if (curNode->ptr == ptr) {
			addNode (freeHead, ptr, curNode->size);
			if (i != 0) nodeAt (usedHead, i - 1)->next = curNode->next;
			return 0;
		}
		curNode = curNode->next;
	}
	return 1;
}

void * heap_alloc (size_t bytes) {
	void * ptr = 0;
	
	node_t * curNode = freeHead;
	
	size_t i;
	for (i = 0; i < freeHead->len; i++) {
		// If we found a free block with enough space, set the pointer
		// and link the block's next pointer to the previous block's.
		if (curNode->size >= bytes) {
			ptr = curNode->ptr;
			if (i != 0) nodeAt (freeHead, i - 1)->next = curNode->next;
			break;
		}
		// Cycle to the next node.
		curNode = curNode->next;
	}
	
	// If there were no matching free blocks, then just
	// allocate some new memory.
	if (ptr == 0) {
		ptr = heap_internalAlloc (bytes);
	}
	
	addNode (usedHead, ptr, bytes);
}
