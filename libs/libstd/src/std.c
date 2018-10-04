#include "std.h"

double atof(const char *s)
{
	int signo = 1, pos_coma = -1;
	double num=0.0;
	size_t i = 0, n = strlen(s);

	if(s[i] == '-')
	{
		signo = -1;
		i++;
	}

	for(; i < n ; i++)
	{
		if(s[i] >= '0' && s[i] <= '9')			// es un numero
		{
			if(pos_coma < 0)					// parte entera
			{
				num *= 10;						// desplazo mi coma un lugar a la derecha
				num += (double) (s[i] - '0');	// sumo el num actual
			}
			else								// parte decimal
			// sumo el numero actual con su peso decimal como 10^-(pos a derecha de la coma)
				num += (double) (s[i] - '0') * ipow(10.0, -(i - pos_coma));
		}
		// si hay una coma (y es la primera q veo)
		else if ((s[i] == '.' || s[i] == ',') && pos_coma < 0)
			pos_coma = i;
		// si hay otra cosa en el string, termino ahi
		else
			break;
	}

	return (num * signo);
}

int atoi(const char *s)
{
	int signo = 1, num = 0;
	size_t i=0, n = strlen(s);

	if(s[i] == '-')
	{
		signo = -1;
		i++;
	}

	for(; i < n ; i++)
	{
		if(s[i] < '0' || s[i] > '9')
			break;
		num *= 10;
		num += (s[i] - '0');
	}

	return (num * signo);
}

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
