#ifndef _CALC_H 
#define _CALC_H

#include <stdio.h>
#include "double_linked_lists.h"

#ifndef _ERRORES_MATH
#define _ERRORES_MATH
enum errores {E_NONE, E_SYNTAX, E_MATH};
#endif

#define DECIMAL_DIGITS 15
#define MAX_EXPR_LEN 1024

typedef struct operation {
	char expression[MAX_EXPR_LEN];
	double result;
	int index;
} operation_t;

typedef struct calculator_data {
	double ans;
	int errFlag;
	int index;
	dl_list_t *list;
} calculator_data_t;

// Solves a complex mathematical expression.
// Receives a string with the expression to solve,
// and a pointer to a struct containing:
// an ANS value, being the last valid result
// and an error flag, which is ensured to be set to E_NONE when
// everything is okay, or E_SYNTAX | E_MATH when it corresponds.
// and a pointer to a double linked list with the history of
// solved expressions and their results, and an index number for each.
// The result is returned in the "ans" field of cdata.
void calc_solveExpression(const char *expression, calculator_data_t *cdata);

void consoleCalc(void);

void calculate(const char *expression, calculator_data_t *);

void calc_clearData(calculator_data_t *cdata);
const char *calc_scroll(dl_list_t **_list, int n);
const char *calc_getLastExpr(dl_list_t *list);
int calc_getLastIndex(dl_list_t *list);
void calc_history_rewind(calculator_data_t *cdata);

#endif
