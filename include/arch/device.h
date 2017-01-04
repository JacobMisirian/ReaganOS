#ifndef device_h
#define device_h

#include <stddef.h>
#include <stdint.h>

typedef struct {
	const char * name;
	size_t (* read) (struct device_t *, void *, size_t, uint64_t);
	size_t (* write) (struct device_t *, void *, size_t, uint64_t);
	size_t (* ioctl) (struct device_t *, int, int, int);
	struct device_t * next;
} device_t;

device_t * device_add (const char * name,
						size_t (* read) (struct device_t *, void *, size_t, uint64_t),
						size_t (* write) (struct device_t *, void *, size_t, uint64_t),
						size_t (* ioctl) (struct device_t *, int, int, int));

size_t device_read (device_t * dev, void * ptr, size_t bytes, uint64_t offset);
size_t device_write (device_t * dev, void * ptr, size_t bytes, uint64_t offset);
size_t device_ioctl (device_t * dev, int one, int two, int three);

#endif
