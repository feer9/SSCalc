#ifndef _NOTACION_H
#define _NOTACION_H

#include <stdio.h>
#include <stdlib.h>

#include "libvarious/src/various.h"
#include "libmaths/src/maths.h"
#include "calc.h"
#include "manejo_nodos.h"
#include "nodo.h"



// Parses the given expression for syntax errors
// returns E_NONE when everything is okay
int checkSyntax(const char*);


node_t* infixToPostfix(const char *inf, double ans, int *err);
double solvePostfix (node_t**, int*);
void printNodes(node_t*);

#endif
