#ifndef string_h
#define string_h

int atoi (const char * str);
char * itoa(int num, char * out, int base);
void * memset (unsigned char b, void * ptr, size_t len);
char * strcat (char * str1, const char * str2);
int strchr (const char * str, unsigned char c);
int strcmp (const char * s1, const char * s2);
char * strcpy (const char * str, char * dest);
size_t strlen (const char * str);
char * strrev (char * str);

#endif
