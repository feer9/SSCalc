#include "strings.h"

size_t strlen(const char *s)
{
	size_t n = 0;
	while(s[n] != '\0')
		n++;
	return n;
}

int strcmp(const char *s1, const char *s2)
{
	int i=0;
	
	while(s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;

	return s1[i] - s2[i];
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i=0;

	while(i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	
	if(i==n)
		i--;

	return s1[i] - s2[i];
}

char *strcat(char *dest, const char *src)
{
	size_t i, dest_len = 0;

	while(dest[dest_len] != '\0')
		dest_len++;

	for(i=0; src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return dest;
}

char *strncat(char *dest, const char *src, size_t n)
{
	size_t i, dest_len = 0;

	while(dest[dest_len] != '\0')
		dest_len++;

	for(i=0; i<n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return dest;
}

char *strcpy(char *dest, const char *src)
{
	size_t i;

	for(i=0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for(i=0; i<n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for(; i<n; i++)
		dest[i] = '\0';

	return dest;
}

char *index(const char *s, int c)
{
	size_t i;

	for(i=0; s[i] != '\0'; i++)
		if(s[i] == c)
			return (char*) (s+i);
	
	return NULL;
}

char *rindex(const char *s, int c)
{
	int i;
	int s_len = (int) strlen(s);

	for( i = s_len ; i >= 0 ; i-- )
		if(s[i] == c)
			return (char*) (s+i);

	return NULL;
}

char *strmove(char *dest, const char *src, size_t len)
{
	unsigned int i;

	if(src != dest)
	{
		for(i=0; i<len; i++)
		{
			*(dest + i) = *(src + i);
		}
	}
	return dest;
}

char *strdup(const char *s)
{
	size_t len = strlen(s) + 1;
	char *new = malloc(len);
	
	if(new == NULL)
		return NULL;

	return strncpy(new, s, len);
}