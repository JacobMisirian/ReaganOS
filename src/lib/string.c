#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <lib/stdio.h>
#include <lib/string.h>
#include <mm/heap.h>

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

size_t fstrlen (const char * fstr, va_list args) {
	size_t res = 0;
	
	char * temp [0xF];
	size_t i;
	for (i = 0; fstr [i] != 0; i++) {
		if (fstr [i] == '%' && fstr [i + 1] != 0) {
			i++;
			switch (fstr [i]) {
				case 'c':
					res++;
					break;
				case 'b':
					res += strlen (itoa (va_arg (args, int), temp, 2));
					break;
				case 'd':
					res += strlen (itoa (va_arg (args, int), temp, 10));
					break;
				case 'o':
					res += strlen (itoa (va_arg (args, int), temp, 8));
					break;
				case 's':
					res += strlen (va_arg (args, char *));
					break;
				case 'x':
					res += strlen (itoa (va_arg (args, int), temp, 16));
					break;
				case '%':
					res++;
					break;
			}
		} else {
			res++;
		}
	}
	return res;
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

void * memset (unsigned char b, void * ptr, size_t len) {
	asm volatile ("cld; rep stosb" : "+c" (len), "+D" (ptr) : "a" (b) : "memory");
	return ptr;
}

char * strcat (const char * str1, const char * str2, char * out) {
	size_t outPos = 0;
	
	size_t i;
	for (i = 0; str1 [i] != 0; i++) {
		out [outPos++] = str1 [i];
	}
	for (i = 0; str2 [i] != 0; i++) {
		out [outPos++] = str2 [i];
	}
	out [outPos++] = 0;
	return out;
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

size_t strlen (const char * str) {
	size_t res = 0;
	while (str [res++] != 0);
	return res - 1;
}

char * strlow (char * str) {
	size_t i;
	for (i = 0; str [i] != 0; i++) {
		if (str [i] >= 65 && str [i] <= 90) {
			str [i] += 32;
		}
	}
	return str;
}

int strrchr (const char * str, uint8_t c) {
	int i;
	for (i = strlen (str) - 1; i >= 0; i--) {
		if (str [i] == c) {
			return i;
		}
	}
	return -1;
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

char * strsplit (char * str, uint8_t c, char * out) {
	if (str [0] == NULL) return NULL;
	
	size_t i;
	for (i = 0; str [i] != 0; i++) {
		if (str [i] == c) {
			break;
		}
		out [i] = str [i];
	}
	
	if (str [i] == 0) {
		strcpy (str, out);
		str [0] = NULL;
		return out;
	}
	out [i++] = NULL;
	
	size_t j;
	for (j = 0; str [i] != 0; i++) {
		str [j++] = str [i];
	}
	str [j] = NULL;
	
	return out;
}

int8_t strStarts (const char * str1, const char * str2) {
	size_t len1 = strlen (str1);
	size_t len2 = strlen (str2);
	
	if (len2 > len1) {
		return -1;
	}
	
	size_t i;
	for (i = 0; i < len2; i++) {
		if (str1 [i] != str2 [i]) {
			return -1;
		}
	}
	return 0;
}

char * strup (char * str) {
	size_t i;
	for (i = 0; str [i] != 0; i++) {
		if (str [i] >= 97 && str [i] <= 122) {
			str [i] -= 32;
		}
	}
	return str;
}

char * substr (const char * str, size_t startIndex, size_t endIndex, char * out) {
	size_t i = 0;
	while (startIndex < endIndex) {
		out [i++] = str [startIndex++];
	}
	out [i] = 0;
	return out;
}
