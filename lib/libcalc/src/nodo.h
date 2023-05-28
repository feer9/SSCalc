#ifndef NODO_H
#define NODO_H

#define SI 1
#define NO 0
#define OK 0


typedef enum symbol_t {
	/* binary operators */
	SUM=1, SUBSTRACTION, MULTIPLICATION, DIVISION, POWER,

	/* binary functions */
	ROOT, POW,

	/* unary operators */
	FACTORIAL, MINUS, PLUS,

	/* unary functions */
	SQRT, LOG, LN, SIN, COS, TAN, ABS,

	/* parenthesis */
	PARENTHESIS_OPEN, PARENTHESIS_CLOSE
} symbol_t ;


typedef enum content_t {
	NUMBER=1, B_OPERATOR, U_OPERATOR, B_FUNCTION, U_FUNCTION, PARENTHESIS 
} content_t ;


typedef struct node_t
{
	union {
	double number;
	symbol_t symbol;
	};

	content_t content;

	struct node_t* next;
} node_t;


#endif // NODO_H
