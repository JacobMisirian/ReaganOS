#include <stddef.h>
#include <stdint.h>

#include <lib/memstream.h>
#include <lib/stream.h>
#include <mm/heap.h>

stream_t * stream_memstreamInit (void * ptr, int64_t len) {
	stream_t * stream = (stream_t *) heap_alloc (sizeof (stream_t));
	stream->len = len;
	stream->pos = 0;
	
	char * cptr = (char *)ptr;
	memstream_t * streamData = (stream_t *) heap_alloc (sizeof (stream_t));
	streamData->ptr = cptr;
	
	stream->streamData = streamData;
	stream->peek = memstream_peek;
	stream->write = memstream_write;
	
	return stream;
}

int stream_peek (stream_t * stream) {
	if (stream->pos >= stream->len) {
		return -1;
	}
	return stream->peek (stream);
}

int stream_read (stream_t * stream) {
	int8_t val = stream_peek (stream);
	stream->pos++;
	return val;
}

void stream_write (stream_t * stream, int8_t val) {
	stream->write (stream, val);
	stream->pos++;
}
