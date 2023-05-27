#include "notacion.h"
#include "calc.h"

#ifdef DEBUG
#define DBGPRNT_COLA(x)  printNodes(x)
#define DBGPRNT(...) {printf(__VA_ARGS__);fflush(stdout);}
#else
#define DBGPRNT_COLA(x)
#define DBGPRNT(...)
#endif


static void trim(char *buf)
{
	int i;
	size_t len = strlen(buf);

	for(i=0; buf[i]; i++)
		while (isSpace(buf[i]))
			strmove(buf+i, buf+i+1, len-i);
}


void consoleCalc()
{
	char input[MAX_EXPR_LEN];
	calculator_data_t cdata = {0};

	puts("Scientific Calc v1.0");
	while( getLine("> ", input, sizeof input) != INPUT_OK);
	// see the readline() and getline() functions

	while(strcmp(input, "q") != 0 && strcmp(input, "quit") != 0)
	{
		cdata.errFlag = E_NONE;
		calculate(input, &cdata);

		while( getLine("> ", input, sizeof input) != INPUT_OK);
	}
	// TODO: Add support for arrow keys history
}

void calculate(const char *expression, calculator_data_t *cdata)
{
	double *ans = &cdata->ans;
	int *errorFlag = &cdata->errFlag;

	calc_solveExpression(expression, cdata);

	if(*errorFlag == E_SYNTAX)
		puts("SYNTAX ERROR");
	else if(*errorFlag == E_MATH)
		puts("MATH ERROR");
	else
		printf("= %.*g\n", DECIMAL_DIGITS, *ans);
}

static const char* utf8CharToAscii(wchar_t wchar)
{
	static char c[2] = "";
	switch (wchar)
	{
		case L'×': return "*";
		case L'√': return "sqrt";
		case L'π': return "pi";
		default: break;
	}
	c[0] = c[1] = '\0';
	if(wchar - (wchar & 0x7F) == 0) // if it's a valid ascii     - wchar & ~((wchar_t)0x7F)
		c[0] = *((char*) &wchar);   // directly cast it as ascii

	return c;
}

static void utf8StrToAscii(char **_s)
{
	char *s = *_s;
	size_t bytesIn = strnlen(s, MAX_EXPR_LEN);

	wchar_t *ws = malloc((bytesIn + 1) * sizeof(wchar_t));
	if(!ws) {
		perror("malloc");
		exit(1);
	}

	size_t len = mbstowcs(ws, s, bytesIn);
	char buf[MAX_EXPR_LEN];
	int outLen = 0;

	for(int iw=0; iw < len; ++iw)
	{
		const char *tmp = utf8CharToAscii(ws[iw]);
		size_t tmpLen =  strlen(tmp);
		strncpy(&buf[outLen], tmp, tmpLen);
		outLen += (int)tmpLen;
	}
	buf[outLen] = '\0';

	char *newS = s;
	if(outLen > bytesIn) {
		newS = realloc(s, outLen+1);
		if(newS)
			*_s = newS;
		else
			outLen = bytesIn;
	}
	strncpy(newS, buf, bytesIn+1);

	free(ws);
}

static operation_t *newOperation(const char* expr, double result, int idx)
{
	operation_t *new = malloc(sizeof(operation_t));
	if(!new) {
		perror("malloc");
		exit(1);
	}

	strncpy(new->expression, expr, sizeof new->expression);
	new->result = result;
	new->index = idx;

	return new;
}

// this function assumes the first node has the greater index
static int getListSize(dl_list_t *list)
{
	int idx = 0;

	if(list && list->d) {
		while (list->prev != NULL)
			list = list->prev;
		idx = ((operation_t *) list->d)->index;
	}
	return idx;
}

int calc_getLastIndex(dl_list_t *list)
{
	if(list && list->d)
		return ((operation_t*)list->d)->index;

	return 0;
}

const char *calc_getLastExpr(dl_list_t *list)
{
	if(list && list->d)
		return ((operation_t*)list->d)->expression;

	return "";
}

const char *calc_scroll(dl_list_t **_list, int n)
{
	dl_list_t *list = *_list;
	while(list && n) {
		if(n < 0) {
			if(list->next)
				list = list->next;
			n++;
		}
		else {
			if(list->prev)
				list = list->prev;
			n--;
		}
		if(list) *_list = list;
	}
	return calc_getLastExpr(list);
}

void calc_history_rewind(calculator_data_t *cdata)
{
	if(cdata) {
		dl_list_t **list = &cdata->list;
		if (*list)
			while ((*list)->prev)
				*list = (*list)->prev;

		cdata->index = (*list)->d->index + 1;
	}
}

void calc_clearData(calculator_data_t *cdata)
{
	if(cdata)
	{
		cdata->ans = 0.0;
		list_destroy(&cdata->list);
	}
}

// fixme: 2e3 = 8.1548 ¿?¿? 2E3 doesn't work either
void calc_solveExpression(const char* expression, calculator_data_t *cdata)
{
	if(!expression || !cdata) return;

	node_t   *COLA = NULL;
	int *errorFlag = &cdata->errFlag;
	double    *ans = &cdata->ans;
	char     *expr = strdup(expression);;

	trim(expr); // remove spaces
	utf8StrToAscii(&expr);  // dirty trick to not support utf-8 :-)

	*errorFlag = checkSyntax(expr);
	if(*errorFlag == E_NONE)
	{
		COLA = infixToPostfix(expr, *ans, errorFlag);
		DBGPRNT_COLA(COLA);
		*ans = solvePostfix(&COLA, errorFlag);

		if(*errorFlag == E_NONE)
		{
			int idx = getListSize(cdata->list)+1;
			operation_t *new_op = newOperation(expr, *ans, idx);
			dl_list_t *node = list_new_node(new_op);
			list_prepend_node(node, &cdata->list);
			cdata->index = idx+1;
		}
	}

	free(expr);

	DBGPRNT("in calc_solveExpression(): result = %lf\n", result);
}
