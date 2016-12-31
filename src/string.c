#include <stddef.h>
#include <stdint.h>

size_t strlen (const char * str) {
	size_t res = 0;
	while (str [res++] != 0);
	return res;
}

void * memset (unsigned char b, void * ptr, size_t len) {
	asm volatile ("cld; rep stosb" : "+c" (len), "+D" (ptr) : "a" (b) : "memory");
	return ptr;
}
