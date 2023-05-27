#include "various.h"

int getLine (const char *prmpt, char *buff, size_t sz)
{
	// Size zero or one cannot store enough, so don't even
	// try - we need space for at least newline and terminator.
	if (sz < 2)
	    return INPUT_SMALL_BUFF;

	// Output prompt.
	if (prmpt != NULL) {
	    fputs(prmpt, stdout);
	    fflush (stdout);
	}

	// Get line with buffer overrun protection.
	if (fgets (buff, (int)sz, stdin) == NULL)
	    return INPUT_EMPTY;

	size_t lastPos = strlen(buff) - 1;

	// If lastPos == 0 (strlen(buff) == 1) no string was input
	if (lastPos == 0)
		return INPUT_EMPTY;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[lastPos] != '\n') {
	    int ch, extra = 0;
	    while (((ch = getchar()) != '\n') && (ch != EOF))
	        extra = 1;
	    return (extra == 1) ? INPUT_OVERFLOW : INPUT_OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[lastPos] = '\0';
	return INPUT_OK;
}

int isSpace(int c)
{
	switch(c)
	{
		case ' ' :
		case '\f':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
			return c;
	}

	return 0;
}

int isAlpha(int c)
{
	if(c >= 'a' && c <= 'z')
		return c;
	
	if(c >= 'A' && c <= 'Z')
		return c;

	return 0;
}
