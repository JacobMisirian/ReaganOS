#include <stddef.h>
#include <stdint.h>

#include <lib/memstream.h>
#include <lib/stream.h>

int8_t memstream_peek (stream_t * stream) {
	memstream_t * memstream = (memstream_t *)stream->streamData;
	
	return memstream->ptr [stream->pos];
}

void memstream_write (stream_t * stream, int8_t val) {
	memstream_t * memstream = (memstream_t *)stream->streamData;
	
	memstream->ptr [stream->pos] = val;
}
