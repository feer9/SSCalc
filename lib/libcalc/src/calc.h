#ifndef _CALC_H 
#define _CALC_H

#ifndef _ERRORES_MATH
#define _ERRORES_MATH
enum errores {E_NONE, E_SYNTAX, E_MATH};
#endif

#define DECIMAL_DIGITS 15

#include <stdio.h>

// Solves a complex mathematical expression.
// Receives an ANS value to use when necessary (to future implementation)
// and an error flag, which is ensured to be E_NONE when everything is okay,
// or E_SYNTAX | E_MATH when it corresponds.
double solveExpression(const char *expression, double ans, int *errorFlag);

void consoleCalc(void);

int calculate(const char *expression, double *ans, int *errorFlag);

#endif
