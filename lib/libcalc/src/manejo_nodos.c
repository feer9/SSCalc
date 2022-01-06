#include "manejo_nodos.h"

void apilar(int content, int c, node_t** P)
{
	node_t* new = (node_t*) malloc(sizeof(node_t));
	if(new == NULL)
	{
		perror("malloc");
		exit(1);
	}

	// Si hay espacio en disco, carga el dato
	new->content = content;

	if(content == NUMBER)
		new->number = 0.0;
	else
		new->symbol = c;

	// Se lo coloca en la pila
	new->next = *P;
	*P = new;
}

void acolar(int content, int c, node_t** P)
{
	node_t* new = (node_t*) malloc(sizeof(node_t));
	if(new == NULL)
	{
		perror("malloc");
		exit(1);
	}

	new->next = NULL;
	new->content = content;

	if(content == NUMBER)
		new->number = 0.0;
	else
		new->symbol = c;

	if( *P == NULL )
		*P = new;
	else
	{
		node_t *last = *P;
		while(last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void acolarNumero(double n, node_t** C)
{
	node_t *aux;
	node_t *new = (node_t*) malloc(sizeof(node_t));
	if(new == NULL)
	{
		perror("malloc");
		exit(1);
	}

	// Si hay espacio en disco, carga el dato
	new->number = n;
	new->content = NUMBER;
	new->next = NULL;
	// Se lo coloca en la Cola
	if(*C == NULL)
		// Si lo Cola está vacía
		*C = new;
	else
	{	// Si hay datos en la cola
		aux = *C;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
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
}

