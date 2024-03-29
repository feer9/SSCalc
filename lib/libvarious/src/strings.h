#ifndef _STRINGS_H
#define _STRINGS_H

#include <stdlib.h>
#include <stddef.h>

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t max);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
int strcasecmp(const char *s1, const char *s2);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *index(const char *s, int c);
char *rindex(const char *s, int c);
char *strmove(char *dest, const char *src, size_t len);
char *strdup(const char *s);

#endif // _STRINGS_H