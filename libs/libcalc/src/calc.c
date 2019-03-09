#include <stdio.h>
#include "notacion.h"
#include "calc.h"

#define _DEBUG_ 1
#define _DBGPRNT_ENABLE_ 1
#define DBGPRNT {if(_DEBUG_ && _DBGPRNT_ENABLE_) mostrar(COLA);}

#define DECIMAL_DIGITS 15



void consoleCalc()
{
	char input[256];
	double res = 0.0;
	double ans = 0.0;
	int errorFlag = E_NO;

	puts("Scientific Calc v0.9");
	while( getLine("> ", input, sizeof input) != INPUT_OK);

	while(strcmp(input, "q") && strcmp(input, "quit"))
	{
		res = resolverExpresion(input, ans, &errorFlag);
		if(errorFlag == E_SINTAXIS)
			puts("error de sintaxis");
		else if(errorFlag == E_MATH)
			puts("error matematico");
		else
		{
			printf("= %.10g\n", res);
			ans = res;
		}

		errorFlag = 0;

		while( getLine("> ", input, sizeof input) != INPUT_OK);
	}
}

double resolverExpresion(const char* expr, double ans, int* errorFlag)
{
	nodo* COLA = NULL;
	
	if(checkSintax(expr))
	{
		*errorFlag = E_SINTAXIS;
		return 0.0;
	}

	COLA = infijaAPostfija(expr, ans);
	DBGPRNT;
	return resolverPostfija(&COLA, errorFlag);
}
