#ifndef _MANEJO_NODOS_H
#define _MANEJO_NODOS_H


#include "notacion.h"
#include "nodo.h"


void apilar(char, char, nodo**);
void acolarNumero(double, nodo**);
nodo* sacar(nodo**);
void pasarACola(nodo** nodo_origen, nodo** cola_destino);
void vaciar(nodo**);
void pasarAPila(nodo** cola, nodo** pila);
void eliminar(nodo**);


#endif
