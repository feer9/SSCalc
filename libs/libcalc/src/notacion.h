#ifndef _NOTACION_H
#define _NOTACION_H

#include <stdio.h>
#include <stdlib.h>

#include "../../libvarious/src/various.h"
#include "../../libmaths/src/maths.h"
#include "calc.h"
#include "manejo_nodos.h"
#include "nodo.h"



int checkSintax(const char*);
int checkMath(double n1, char op, double n2);
nodo* infijaAPostfija(const char*, double);
int esNumero(char);
int esOperacion(char);
double resolverPostfija(nodo**, int*);
nodo* resolver(nodo* n1, nodo* n2, nodo** op, int *errorFlag);
void mostrar(nodo*);

#endif
