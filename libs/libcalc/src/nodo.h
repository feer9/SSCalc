#ifndef NODO_H
#define NODO_H

#define SI 1
#define NO 0
#define OK 0
enum operaciones {SUMA=1,RESTA,MULTIPLICACION,DIVISION,POTENCIA,PARENTESIS_A,PARENTESIS_C,ESPACIO,OpMAX};
enum {NUMERO,OPERADOR,SIMBOLO};

typedef struct _nodo
{
	union{
	double numero;
	char operador; // Un operador puede ser +, -, *, ó /
	char simbolo;  // por ahora seria un parentesis
	};
	short int contenido; // contenido del nodo: NUMERO, OPERADOR o SIMBOLO

	struct _nodo* sig;
} nodo;

#endif // NODO_H
