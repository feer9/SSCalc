#include "notacion.h"
#include "calc.h"

#ifdef DEBUG
#define DBGPRNT_COLA(x)  printNodes(x)
#define DBGPRNT(...) {printf(__VA_ARGS__);fflush(stdout);}
#else
#define DBGPRNT_COLA(x)
#define DBGPRNT(...)
#endif


static void trim(char *buf)
{
	int i;
	size_t len = strlen(buf);

	for(i=0; buf[i]; i++)
		while (isSpace(buf[i]))
			strmove(buf+i, buf+i+1, len-i);
}


void consoleCalc()
{
	char input[256];
	double ans = 0.0;
	int errorFlag = E_NONE;

	puts("Scientific Calc v1.0");
	while( getLine("> ", input, sizeof input) != INPUT_OK);
	// see the readline() and getline() functions

	while(strcmp(input, "q") != 0 && strcmp(input, "quit") != 0)
	{
		errorFlag = E_NONE;
		calculate(input, &ans, &errorFlag);

		while( getLine("> ", input, sizeof input) != INPUT_OK);
	}
}

int calculate(const char *expression, double *ans, int *errorFlag)
{
	double result, _ans = (ans != NULL ? *ans : 0.0);
	int _err = 0; if(errorFlag == NULL) errorFlag = &_err;

	result = solveExpression(expression, _ans, errorFlag);

	if(*errorFlag == E_SYNTAX)
		puts("SYNTAX ERROR");
	else if(*errorFlag == E_MATH)
		puts("MATH ERROR");
	else
	{
		printf("= %.*g\n", DECIMAL_DIGITS, result);
		if (ans) *ans = result;
	}

	return *errorFlag;
}

static const char* utf8CharToAscii(wchar_t wchar)
{
	static char c[2] = "";
	switch (wchar)
	{
		case L'×': return "*";
		case L'√': return "sqrt";
		case L'π': return "pi";
	}
	c[0] = c[1] = '\0';
	if(wchar - (wchar & 0x7F) == 0) // if it's a valid ascii     - wchar & ~((wchar_t)0x7F)
		c[0] = *((char*) &wchar);      // directly cast it as ascii

	return c;
}

static void utf8StrToAscii(char **_s)
{
	char *s = *_s;
	size_t bytesIn = strnlen(s, 256);

	wchar_t *ws = malloc((bytesIn + 1) * sizeof(wchar_t));
	if(!ws) {
		perror("malloc");
		exit(1);
	}

	size_t len = mbstowcs(ws, s, bytesIn);
	char buf[256];
	int outLen = 0;

	for(int iw=0; iw < len; ++iw)
	{
		const char *tmp = utf8CharToAscii(ws[iw]);
		size_t tmpLen =  strlen(tmp);
		strncpy(&buf[outLen], tmp, tmpLen);
		outLen += (int)tmpLen;
	}
	buf[outLen] = '\0';

	char *newS = s;
	if(outLen > bytesIn) {
		newS = realloc(s, outLen+1);
		if(newS)
			*_s = newS;
		else
			outLen = bytesIn;
	}
	strncpy(newS, buf, bytesIn+1);

	free(ws);
}

// fixme: 2e3 = 8.1548 ¿?¿? 2E3 doesn't work either
double solveExpression(const char* expression, double ans, int* errorFlag)
{
	node_t* COLA = NULL;
	double result = 0.0;
	int _err = 0; if(errorFlag == NULL) errorFlag = &_err;
	char* expr = strdup(expression);
	if(expr == NULL)
	{
		perror("malloc");
		exit(1);
	}

	trim(expr); // remove spaces
	utf8StrToAscii(&expr);  // dirty trick to not support utf-8 :-)

	*errorFlag = checkSyntax(expr);
	if(*errorFlag == E_NONE)
	{
		COLA = infixToPostfix(expr, ans, errorFlag);
		DBGPRNT_COLA(COLA);
		result = solvePostfix(&COLA, errorFlag);
	}
	free(expr);
	DBGPRNT("in solveExpression(): result = %lf\n", result);
	return result;
}
