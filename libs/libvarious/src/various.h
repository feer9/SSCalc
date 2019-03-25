#ifndef _VARIOUS_H
#define _VARIOUS_H

#include <stddef.h>
#include <stdio.h>

#include "strings.h"
#include "std.h"

// Return values for getLine
#define INPUT_OK         0
#define INPUT_EMPTY      1
#define INPUT_OVERFLOW   2
#define INPUT_SMALL_BUFF 3


int getLine (const char *prmpt, char *buff, size_t sz);
int isSpace (int c);

#endif // _VARIOUS_H