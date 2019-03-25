#ifndef NODO_H
#define NODO_H

#define SI 1
#define NO 0
#define OK 0

enum bOperations { SUMA=1, RESTA, MULTIPLICACION, DIVISION,
			POTENCIA, ROOT, PARENTESIS_A, PARENTESIS_C, OpMAX
} ;

enum uOperations {
	SQRT, SIN, COS, TAN, FACTORIAL, 
} ;

enum {NUMERO,OPERADOR,SIMBOLO};

typedef struct node
{
	union {
	double Number;
	char Operator; // Un operador puede ser +, -, *, /, ó ^
	char Symbol;   // por ahora seria un parentesis
	};
	int Content;   // contenido del nodo: NUMERO, OPERADOR o SIMBOLO

	struct node* next;
} node_t;

#endif // NODO_H
