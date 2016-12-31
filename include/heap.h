#ifndef heap_h
#define heap_h

#include "heapBlock.h"

static void * nextPtr;

static node_t * freeHead;
static node_t * usedHead;

void heap_init ();
void * heap_alloc ();

#endif
