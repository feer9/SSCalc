#ifndef _MY_STDLIB_H
#define _MY_STDLIB_H

#include "../../libmaths/src/maths.h"
#include <stddef.h>

int atoi(const char *s);
double atof(const char *s);

size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *index(const char *s, int c);
char *rindex(const char *s, int c);

#endif