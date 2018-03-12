/*
 *known issues:
 * la implementacion de pow en la libreria da cualquier cosa para bases de 0,algo
 * aparte esta aceptando bases negativas con exponente real, cosa que da resultados imaginarios
 *
 *
 */ 

#include <stdio.h>
#include "inc/infija_a_postfija.h"
#include "libcalc.h"

#define _DEBUG_ 0
#define _DBGPRNT_ENABLE_ 1
#define _DBGPRNT_ {if(_DEBUG_ && _DBGPRNT_ENABLE_) mostrar(COLA);}

#define DECIMAL_DIGITS 13


 //int argc, char* argv[]);

enum errores{E_NO,E_SINTAXIS,E_MATH};
int m_error = E_NO;


void consoleCalc()  //int argc, char* argv[])
{
	char input[256];
	double res = 0.0;

//	if (argc == 2 && strlen(input) > 2) // argumento de entrada
//	{
//		strcpy(input, argv[1]);
//	}
//	else
//	{
		scanf("%s",input);
//	}

	while(strcmp(input, "quit") && strcmp(input, "exit"))
	{
		res = resolverExpresion(input);
		if(m_error == E_SINTAXIS)
			printf("error de sintaxis\n");
		else if(m_error == E_MATH)
			printf("error matematico\n");
		else
			printf("= %f\n", res);

		m_error = 0;

		scanf("%s",input);
	}
}

double resolverExpresion(const char* expr)
{
	nodo* COLA = NULL;
	if(check_expr(expr))
	{
		m_error = E_SINTAXIS;
		return 0.0;
	}
	COLA = infijaAPostfija(expr);
	_DBGPRNT_
	return resolver_postfija(&COLA);
}
