#include "notacion.h"
#include "calc.h"

#define _DBGPRNT_ 1
#if _DBGPRNT_
#define DBGPRNT_COLA(x)  mostrar(x)
#define DBGPRNT(...) {printf(__VA_ARGS__);fflush(stdout);}
#else
#define DBGPRNT_COLA(x)
#define DBGPRNT(...)
#endif

// TODO: si despues de un numero viene un parentesis,
// insertar un *

void consoleCalc()
{
	char input[256];
	double result = 0.0;
	double ans = 0.0;
	int errorFlag = E_NO;

	puts("Scientific Calc v0.9");
	while( getLine("> ", input, sizeof input) != INPUT_OK);

	while(strcmp(input, "q") && strcmp(input, "quit"))
	{
		result = resolverExpresion(input, ans, &errorFlag);
		if(errorFlag == E_SINTAXIS)
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

double resolverExpresion(const char* expr, double ans, int* errorFlag)
{
	nodo* COLA = NULL;
	double result = 0.0;
	
	*errorFlag = checkSintax(expr);
	if(*errorFlag == E_NO)
	{
		COLA = infijaAPostfija(expr, ans);
		DBGPRNT_COLA(COLA);
		result = resolverPostfija(&COLA, errorFlag);
	}
	DBGPRNT("in ResolverExpresion(): result = %lf\n", result);
	return result;
}
