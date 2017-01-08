#ifndef heapBlock_h
#define heapBlock_h

#include <stdint.h>
#include <stddef.h>

typedef struct {
	void * ptr;
	size_t size;
	struct node * next;
} node_t;

#endif
