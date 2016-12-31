#ifndef heapBlock_h
#define heapBlock_h

#include <stdint.h>

typedef struct node {
	void * ptr;
	size_t size;
	size_t len;
	struct node * next;
} node_t;

#endif
