#ifndef memstream_h
#define memstream_h

#include <stddef.h>
#include <stdint.h>

#include <lib/stream.h>

typedef struct {
	int8_t * ptr;
} memstream_t;

int8_t memstream_peek (stream_t * stream);
void memstream_write (stream_t * stream, int8_t val);

#endif
