#include "manejo_nodos.h"

void apilar(char contenido, char c, nodo** P)
{
	nodo* nuevo;

	nuevo = (nodo*) malloc(sizeof(nodo));
	if(nuevo == NULL)
	{
		perror("ERROR, Memoria Insuficiente");
		exit(1);
	}
	// Si hay espacio en disco, carga el dato
	nuevo->contenido = contenido;

	if(contenido == OPERADOR)
		nuevo->operador = c;
	else if(contenido == SIMBOLO)
		nuevo->simbolo = c;
	else
		nuevo->numero = 0.0;

	// Se lo coloca en la pila
	nuevo->sig = *P;
	*P = nuevo;

	return;
}

void acolarNumero(double n, nodo** C)
{
	nodo *nuevo, *aux;

	nuevo = (nodo*) malloc(sizeof(nodo));
	if(nuevo == NULL)
	{
		perror("ERROR, Memoria Insuficiente");
		exit(1);
	}

	// Si hay espacio en disco, carga el dato
	nuevo->numero = n;
	nuevo->contenido = NUMERO;
	nuevo->sig = NULL;
	// Se lo coloca en la Cola
	if(*C == NULL)
		// Si lo Cola está vacía
		*C = nuevo;
	else
	{	// Si hay datos en la cola
		aux = *C;
		while (aux->sig != NULL)
			aux = aux->sig;
		aux->sig = nuevo;
	}

	return;
}

// Funcion que saca el primer elemento de una pila o cola, y devuelve su dirección (no lo elimina).
nodo* sacar(nodo** N)
{
	nodo* aux = NULL;
	if(*N != NULL)
	{
		aux = *N;
		*N = (*N)->sig;
	}
	return aux;
}

// recibe un nodo y lo inserta en una cola
void pasarACola(nodo** nodo_origen, nodo** cola_destino)
{
	nodo* aux;

	(*nodo_origen)->sig = NULL;
	if(*cola_destino == NULL)
		// Si lo Cola está vacía
		*cola_destino = *nodo_origen;
	else
	{	// Si hay datos en la cola
		aux = *cola_destino;
		while (aux->sig != NULL)
			aux = aux->sig;
		aux->sig = *nodo_origen;
	}
	return;
}


// meter el nodo origen (de una cola) en una pila
void pasarAPila(nodo** cola, nodo** pila)
{
	nodo* aux;
	if(*cola != NULL)
	{
		aux = *cola;
		*cola = (*cola)->sig;
		aux->sig = *pila;
		*pila = aux;
	}
	return;
}

void vaciar(nodo** N)
{
	nodo* aux;
	while (*N != NULL)
	{
		aux = *N;
		*N = aux->sig;
		free(aux);
	}
	return;
}

void eliminar(nodo** N)
{
	nodo* aux;
	if(*N != NULL)
	{
		aux = *N;
		*N = aux->sig;
		free(aux);
	}
	return;
}

