#include <stddef.h>
#include <stdint.h>

#include "string.h"	

size_t strlen (const char * str) {
	size_t res = 0;
	while (str [res++] != 0);
	return res - 1;
}

int strcmp (const char * s1, const char * s2) {
	size_t len1 = strlen (s1);
	size_t len2 = strlen (s2);
	
	size_t len = len1 > len2 ? len2 : len1;
	size_t i;
	for (i = 0; i < len; i++) {
		if (s1 [i] != s2 [i]) {
			return s1 [i] < s2 [i] ? -1 : 1;
		}
	}
	return 0;
}


char * strrev (char * str) {
	size_t len = strlen (str);
	size_t mid = len % 2 == 0 ? len / 2 : (len + 1) / 2;
	
	size_t i;
	size_t j;
	for (i = 0, j = len - 1; i < mid; i++, j--) {
		char temp = str [i];
		str [i] = str [j];
		str [j] = temp;
	}
	return str;
}

char * itoa(int num, char * out, int base) {
    int i = 0;
    int isNegative = 0;
    
    if (num == 0) {
        out [i++] = '0';
        out [i] = '\0';
        return out;
    }
 
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }
    
    while (num != 0) {
        int rem = num % base;
        out [i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num/base;
    }
    
    if (isNegative)
        out [i++] = '-';
 
    out [i] = 0;
    
    strrev (out);
    return out;
}

int indexOf (const char * str, unsigned char c) {
	int len = strlen (str);
	int i;
	for (i = 0; i < len; i++) {
		if (str [i] == c) {
			return i;
		}
	}
	return -1;
}

void * memset (unsigned char b, void * ptr, size_t len) {
	asm volatile ("cld; rep stosb" : "+c" (len), "+D" (ptr) : "a" (b) : "memory");
	return ptr;
}
