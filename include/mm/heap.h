#ifndef heap_h
#define heap_h

#include <stdint.h>
#include <stddef.h>

#include <mm/heapBlock.h>

static void * nextPtr;

static node_t * freeHead;
static node_t * usedHead;

void * heap_alloc (size_t bytes);
size_t heap_free (void * ptr);
void heap_init ();

#endif
