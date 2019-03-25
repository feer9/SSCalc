#ifndef _MANEJO_NODOS_H
#define _MANEJO_NODOS_H


#include "notacion.h"
#include "nodo.h"


void apilar(char, char, node_t**);
void acolarNumero(double, node_t**);
node_t* sacar(node_t**);
void pasarACola(node_t** nodo_origen, node_t** cola_destino);
void pasarAPila(node_t** cola, node_t** pila);
void eliminarNodo(node_t**);
void vaciar(node_t**);


#endif
