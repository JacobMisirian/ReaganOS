#ifndef stream_h
#define stream_h

#define STREAM_MEMSTREAM 1
#define STREAM_FILESTREAM 2

typedef struct {
	uint32_t streamType;
	int64_t pos;
	int64_t len;
	int8_t (* peek) (struct stream_t *);
	void (* write) (struct stream_t *, int8_t);
	void * streamData;
	
} stream_t;

stream_t * stream_memstreamInit (void * ptr, int64_t len);
int stream_peek (stream_t * stream);
int stream_read (stream_t * stream);
void stream_write (stream_t * stream, int8_t val);

#endif
