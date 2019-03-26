#ifndef _NOTACION_H
#define _NOTACION_H

#include <stdio.h>
#include <stdlib.h>

#include "../../libvarious/src/various.h"
#include "../../libmaths/src/maths.h"
#include "calc.h"
#include "manejo_nodos.h"
#include "nodo.h"



// Parses the given expression for sintax errors
// returns E_NO when everything is okay
int checkSintax(const char*);


int checkMath(double n1, char op, double n2);
node_t* infixToPostfix(const char*, double);
int isNumber(char);
int isOperation(char);
double solvePostfix(node_t**, int*);
node_t* solve(node_t* n1, node_t* n2, node_t** operation, int *errorFlag);
void printNodes(node_t*);

#endif
