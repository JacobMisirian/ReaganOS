#include <stddef.h>
#include <stdint.h>

#include <lib/string.h>	

size_t strlen (const char * str) {
	size_t res = 0;
	while (str [res++] != 0);
	return res - 1;
}

char * strcat (char * str1, const char * str2) {
	size_t len = strlen (str1);
	size_t i;
	for (i = 0; str2 [i] != 0; i++) {
		str1 [len + i] = str2 [i];
	}
	str1 [len + i + 1] = 0;
	return str1;
}

int strcmp (const char * s1, const char * s2) {
    while(* s1 && (* s1 == * s2)) {
        s1++;
        s2++;
    }
    return * (const uint8_t *)s1 - * (const uint8_t *)s2;
}

char * strcpy (const char * str, char * dest) {
	size_t i;
	for (i = 0; str [i] != 0; i++) {
		dest [i] = str [i];
	}
	dest [i] = 0;
	return dest;
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

int atoi (const char * str) {
	int res = 0;
	int mul = 1;
	size_t i = 0;
	
	if (str [0] == '-') {
		mul = -1;
		i = 1;
	}
	
	while (str [i] != 0) {
		res = res * 10 + str [i++] - '0';
	}
	
	return res * mul;
}

int strchr (const char * str, unsigned char c) {
	int i;
	for (i = 0; str [i] != 0; i++) {
		if (str [i] == c) {
			return i;
		}
	}
	return -1;
}

char * substr (const char * str, size_t startIndex, size_t endIndex, char * out) {
	size_t i = 0;
	while (startIndex < endIndex) {
		out [i++] = str [startIndex++];
	}
	out [i] = 0;
	return out;
}

int strrchr (const char * str, unsigned char c) {
	int i;
	for (i = strlen (str) - 1; i >= 0; i--) {
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
