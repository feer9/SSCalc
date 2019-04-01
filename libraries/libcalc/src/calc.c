#include "notacion.h"
#include "calc.h"

#define _DBGPRNT_ 0
#if _DBGPRNT_
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
	double result = 0.0;
	double ans = 0.0;
	int errorFlag = E_NONE;

	puts("Scientific Calc v1.0");
	while( getLine("> ", input, sizeof input) != INPUT_OK);

	while(strcmp(input, "q") && strcmp(input, "quit"))
	{
		result = solveExpression(input, ans, &errorFlag);
		if(errorFlag == E_SYNTAX)
			puts("error de sintaxis");
		else if(errorFlag == E_MATH)
			puts("error matematico");
		else
		{
			printf("= %.*g\n", DECIMAL_DIGITS, result);
			ans = result;
		}

		errorFlag = 0;

		while( getLine("> ", input, sizeof input) != INPUT_OK);
	}
}

double solveExpression(const char* expression, double ans, int* errorFlag)
{
	node_t* COLA = NULL;
	double result = 0.0;
	char* expr = strdup(expression);
	if(expr == NULL)
	{
		perror("malloc");
		exit(1);
	}

	trim(expr); // remove spaces
	*errorFlag = checkSintax(expr);
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
