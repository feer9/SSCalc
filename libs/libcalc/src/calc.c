#include <stdio.h>
#include "notacion.h"
#include "calc.h"

#define _DEBUG_ 1
#define _DBGPRNT_ENABLE_ 0
#define DBGPRNT {if(_DEBUG_ && _DBGPRNT_ENABLE_) mostrar(COLA);}

#define DECIMAL_DIGITS 15



void consoleCalc()
{
	char input[256];
	double res = 0.0;
	double ans = 0.0;
	int errorFlag = E_NO;

	scanf("%s",input);

	while(strcmp(input, "quit") && strcmp(input, "exit"))
	{
		res = resolverExpresion(input, ans, &errorFlag);
		if(errorFlag == E_SINTAXIS)
			printf("error de sintaxis\n");
		else if(errorFlag == E_MATH)
			printf("error matematico\n");
		else
		{
			printf("= %.15lf\n", res);
			ans = res;
		}

		errorFlag = 0;

		scanf("%s",input);
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
