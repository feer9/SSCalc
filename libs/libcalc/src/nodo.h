#ifndef NODO_H
#define NODO_H

#define SI 1
#define NO 0
#define OK 0


typedef enum {
	/* binary operators */
	SUM=1, SUBSTRACTION, MULTIPLICATION, DIVISION, POWER,

	/* binary functions */
	ROOT, POW,

	/* unary operators */
	FACTORIAL, MINUS,

	/* unary functions */
	SQRT, LOG, LN, SIN, COS, TAN,

	/* parenthesis */
	PARENTHESIS_OPEN, PARENTHESIS_CLOSE
} symbol_t ;


typedef enum {
	NUMBER=1, B_OPERATOR, U_OPERATOR, B_FUNCTION, U_FUNCTION, PARENTHESIS 
} content_t ;

typedef struct node
{
	union {
	double number;
	symbol_t symbol;
	};

	content_t content;

	struct node* next;
} node_t;

#endif // NODO_H
