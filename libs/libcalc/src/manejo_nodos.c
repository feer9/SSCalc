#include "manejo_nodos.h"

void apilar(char Content, char c, node_t** P)
{
	node_t* nuevo;

	nuevo = (node_t*) malloc(sizeof(node_t));
	if(nuevo == NULL)
	{
		perror("malloc");
		exit(1);
	}
	// Si hay espacio en disco, carga el dato
	nuevo->Content = Content;

	if(Content == OPERADOR)
		nuevo->Operator = c;
	else if(Content == SIMBOLO)
		nuevo->Symbol = c;
	else
		nuevo->Number = 0.0;

	// Se lo coloca en la pila
	nuevo->next = *P;
	*P = nuevo;

	return;
}

void acolarNumero(double n, node_t** C)
{
	node_t *nuevo, *aux;

	nuevo = (node_t*) malloc(sizeof(node_t));
	if(nuevo == NULL)
	{
		perror("malloc");
		exit(1);
	}

	// Si hay espacio en disco, carga el dato
	nuevo->Number = n;
	nuevo->Content = NUMERO;
	nuevo->next = NULL;
	// Se lo coloca en la Cola
	if(*C == NULL)
		// Si lo Cola está vacía
		*C = nuevo;
	else
	{	// Si hay datos en la cola
		aux = *C;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = nuevo;
	}

	return;
}

// Funcion que saca el primer elemento de una pila o cola
// y devuelve su dirección (no lo elimina).
node_t* sacar(node_t** N)
{
	node_t* aux = NULL;
	if(*N != NULL)
	{
		aux = *N;
		*N = (*N)->next;
		aux->next = NULL;
	}
	return aux;
}

// recibe un nodo y lo inserta en una cola
void pasarACola(node_t** nodo_origen, node_t** cola_destino)
{
	node_t* aux;

	(*nodo_origen)->next = NULL;
	if(*cola_destino == NULL)
		// Si lo Cola está vacía
		*cola_destino = *nodo_origen;
	else
	{	// Si hay datos en la cola
		aux = *cola_destino;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = *nodo_origen;
	}
	return;
}


// meter el nodo origen (de una cola) en una pila
void pasarAPila(node_t** cola, node_t** pila)
{
	node_t* aux;
	if(*cola != NULL)
	{
		aux = *cola;
		*cola = (*cola)->next;
		aux->next = *pila;
		*pila = aux;
	}
	return;
}

void vaciar(node_t** N)
{
	node_t* aux;
	while (*N != NULL)
	{
		aux = *N;
		*N = aux->next;
		free(aux);
	}
	return;
}

void eliminarNodo(node_t** N)
{
	node_t* aux;
	if(*N != NULL)
	{
		aux = *N;
		*N = aux->next;
		free(aux);
	}
	return;
}

