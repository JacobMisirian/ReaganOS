#ifndef heapBlock_h
#define heapBlock_h

#include <stdint.h>
#include <stddef.h>

typedef struct node {
	void * ptr;
	size_t size;
	struct node * next;
	struct node * pre;
} node_t;

#endif
