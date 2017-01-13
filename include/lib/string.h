#ifndef string_h
#define string_h

#include <stdarg.h>
#include <stddef.h>

int atoi (const char * str);
size_t fstrlen (const char * fstr, va_list args);
char * itoa(int num, char * out, int base);
void * memset (unsigned char b, void * ptr, size_t len);
char * strcat (char * str1, const char * str2);
int strchr (const char * str, unsigned char c);
int strcmp (const char * s1, const char * s2);
char * strcpy (const char * str, char * dest);
size_t strlen (const char * str);
char * strrev (char * str);
char * strsplit (char * str, uint8_t c, char * out);
int8_t strStarts (const char * str1, const char * str2);
char * substr (const char * str, size_t startIndex, size_t endIndex, char * out);

#endif
