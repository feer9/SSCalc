#ifndef _CALC_H 
#define _CALC_H

#ifndef ERRORES_MATH
#define ERRORES_MATH
enum errores {E_NO, E_SINTAXIS, E_MATH};
#endif

double resolverExpresion(const char*, double, int*);
void consoleCalc();

#endif