#ifndef _NOTACION_H
#define _NOTACION_H

#include <stdio.h>
#include <stdlib.h>

#include "../../libstring/src/my_string.h"
#include "../../libstd/src/std.h"
#include "../../libmaths/src/maths.h"
#include "calc.h"
#include "manejo_nodos.h"
#include "nodo.h"



int checkSintax(const char*);
int checkMath(double n1, char op, double n2);
nodo* infijaAPostfija(const char*, double);
int esNum(char);
int esOp(char);
double resolverPostfija(nodo**, int*);
nodo* resolver(nodo* n1, nodo* n2, nodo** op, int *errorFlag);
void mostrar(nodo*);

#endif
