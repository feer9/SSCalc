#include "notacion.h"


static int isNumber     (char);
static double getNumber (const char *str, unsigned int *i);
static int isParenthesis(char);
static int isBOperation (char);
static int isUOperation (char);
static int isUFunction  (const char *inf, unsigned int *i);
static int isBFunction  (const char *inf, unsigned int *i);
static int isConstant   (const char *inf, unsigned int *i, double *num, double ans);

static void push_parenthesis (symbol_t op, node_t **_PILA, node_t **_COLA);
static void push_B_function  (symbol_t op, node_t **_PILA, node_t **_COLA);
static void push_U_operator  (symbol_t op, node_t **_PILA, node_t **_COLA);
static void push_U_function  (symbol_t op, node_t **_PILA, node_t **_COLA);
static void push_B_operator  (symbol_t op, node_t **_PILA, node_t **_COLA);

static void error(int err, int *errFlag, node_t **PILA, node_t **COLA);

static int checkMath_binary(double n1, int op, double n2);
static int checkMath_unary(double n, int op);

static inline int isValidChar(char c)
{
	return (isBOperation(c) | isUOperation(c) | isParenthesis(c));
}



int checkSintax(const char* str)
{
	int c;
	int i = 0;
	int ops_consec = 0;
	int parentesis = 0;
	int tama;
	int comas = 0;
	int esNum;

	tama = (int) strlen(str);
	while(isAlpha(str[i])) i++; // todo: verify if this will work
	c = isValidChar(str[i]);
	if((c >= MULTIPLICATION && c <= POWER) || c == PARENTHESIS_CLOSE)
	
	while(i < tama && parentesis >= 0)
	{
		if (c >= SUM && c <= POWER) {
			ops_consec++;
			comas = 0;
		}
		else {
			ops_consec = 0;
			esNum = isNumber(str[i]);
			if(esNum == 2) { // dot
				comas++;
				if(comas > 1)
					return E_SYNTAX;
			}
			else if(!esNum && !c) {
				// not a number nor another valid thing
				return E_SYNTAX;
			}
		}

		if(ops_consec > 1 && (c != SUM && c != SUBSTRACTION))
		// despues de un operador, solo puede haber un + o un -
			return E_SYNTAX;
		if(ops_consec > 2)
			return E_SYNTAX;

		if (c == PARENTHESIS_OPEN)
			parentesis++;
		else if (c == PARENTHESIS_CLOSE)
			parentesis--;

		i++;
		while(isAlpha(str[i])) i++;
		c = isValidChar(str[i]);
	}

	return (parentesis + ops_consec == 0) ? E_NO : E_SYNTAX;
}

static inline void error(int err, int *errFlag, node_t **PILA, node_t **COLA)
{
	*errFlag = err;
	vaciar(PILA);
	vaciar(COLA);
}

node_t* infixToPostfix(const char* inf, double ans, int *errFlag)
{
	unsigned int i=0;
	symbol_t op = 0;     // actual operation
	content_t last = -1;
	node_t* PILA = NULL;
	node_t* COLA = NULL;
	node_t* node_aux = NULL;
	const size_t tama = strlen(inf); // tamaño de la expresion
	double constant = 0;
	// check for a sign at beggining
	if((op = isBOperation(inf[i])) == SUBSTRACTION || op == SUM)
	{
		acolarNumero(0.0, &COLA);
		apilar(B_OPERATOR, op, &PILA);
		i++;
	}


	while (i < tama)
	{
		if(isNumber(inf[i]))
		{
			acolarNumero(getNumber(&inf[i], &i), &COLA);
			last = NUMBER;
		}
		else if(isConstant(&inf[i], &i, &constant, ans))
		{
			if(last == NUMBER)
				push_B_operator(MULTIPLICATION, &PILA, &COLA);
			acolarNumero(constant, &COLA);
			last = NUMBER;
		}
		else
		{
			if( (op = isParenthesis(inf[i])) != 0)
			{
				if(op == PARENTHESIS_OPEN && last == NUMBER)
					push_B_operator(MULTIPLICATION, &PILA, &COLA);

				push_parenthesis(op, &PILA, &COLA);

				if(op == PARENTHESIS_OPEN && inf[i+1] == '-')
				{
					acolarNumero(0.0, &COLA);
					apilar(B_OPERATOR, SUBSTRACTION, &PILA);
					i++;
				}
				last = PARENTHESIS;
			}

			else if( (op = isBOperation(inf[i])) != 0)
			{
				push_B_operator(op, &PILA, &COLA);
				if(inf[i+1] == '-')
				{
					push_U_operator(MINUS, &PILA, &COLA);
					i++;
				}
				last = B_OPERATOR;
			}

			else if( (op = isUOperation(inf[i])) != 0)
			{
				if(last != NUMBER && last != U_OPERATOR && last != PARENTHESIS) {
					error(E_SYNTAX, errFlag, &PILA, &COLA);
					return NULL;
				}
				push_U_operator(op, &PILA, &COLA);
				last = U_OPERATOR;
			}

			else if( (op = isUFunction(&inf[i], &i)) != 0)
			{
				if(last == NUMBER || last == U_OPERATOR)
					push_B_operator(MULTIPLICATION, &PILA, &COLA);

				push_U_function(op, &PILA, &COLA);
				last = U_FUNCTION;
			}

			else if( (op = isBFunction(&inf[i], &i)) != 0)
			{
				push_B_function(op, &PILA, &COLA);
				last = B_FUNCTION;
			}

			else
			{	// SYNTAX ERROR!!!!
				error(E_SYNTAX, errFlag, &PILA, &COLA);
				return NULL;			
			}
			i++;
		} // else
	} // while

	// por ultimo, todo lo que quede en la pila se pasa a la cola
	while (PILA != NULL)
	{
		node_aux = sacar(&PILA);
		pasarACola(&node_aux, &COLA);
	}

	return COLA;
}


static void push_parenthesis(symbol_t op, node_t **PILA, node_t **COLA)
{
	// si se abre un parentesis, lo meto en la pila
	if (op == PARENTHESIS_OPEN) {
		apilar(PARENTHESIS, op, PILA);
	}

	// al encontrar un parentesis que se cierra ')',
	// mando los elementos de la pila a la cola,
	// hasta encontrar un parentesis que se abra. Este ultimo se elimina.
	else if (op == PARENTHESIS_CLOSE)
	{
		node_t *aux = sacar(PILA);
		/*while (aux != NULL && (aux->content == NUMBER || 
		aux->content == B_OPERATOR || aux->content == U_FUNCTION) )*/
		while (aux != NULL && aux->content != PARENTHESIS )
		{
			pasarACola(&aux, COLA);
			aux = sacar(PILA);
		}
		if(aux->content == PARENTHESIS && aux->symbol == PARENTHESIS_OPEN)
			free(aux);
	}
}



static void push_B_function(symbol_t op, node_t **PILA, node_t **COLA)
{
	// To be done...
}

static void push_U_function(symbol_t op, node_t **PILA, node_t **COLA)
{	// todo: check this
	while(*PILA != NULL && ( (*PILA)->content == U_OPERATOR ) )
//							|| (*PILA)->content == B_FUNCTION ) )
	{
		node_t *aux = sacar(PILA);
		pasarACola(&aux, COLA);
	}
	apilar(U_FUNCTION, op, PILA);
}

static void push_U_operator(symbol_t op, node_t **PILA, node_t **COLA)
{	// todo: check this
	while(*PILA != NULL && ( (*PILA)->content == U_FUNCTION
		|| (*PILA)->content == B_FUNCTION || (*PILA)->content == U_OPERATOR ) )
	{
		node_t *aux = sacar(PILA);
		pasarACola(&aux, COLA);
	}

	apilar(U_OPERATOR, op, PILA);
}

static void push_B_operator(symbol_t op, node_t **PILA, node_t **COLA)
{
	int opPrecedence = 0; // precedence of actual operation
	int headPrecedence;   // precedence of PILA's first element

	switch(op) {
		// si es +, -, *, / ó ^
	case POWER:							opPrecedence += 2; // 2+2+1=5
	case MULTIPLICATION: case DIVISION:	opPrecedence += 2; //   2+1=3
	case SUM: case SUBSTRACTION:		opPrecedence += 1; //     1=1
	default: break;
	}
	/* para suma y resta (1 y 2) si en la pila tengo otras operaciones consecutivas, las tengo que pasar a la cola
	*  para mult y divis (3 y 4) si en la pila tengo mult, div o pot las tengo que pasar a la cola
	*  para potencia (5) solo si en la pila hay otras potencias, las paso a la cola
	*/

	if(*PILA != NULL && (*PILA)->content != PARENTHESIS)
	{
		headPrecedence = (*PILA)->symbol;

		while (*PILA != NULL && ( headPrecedence >= opPrecedence ) )
		{
			node_t *aux = sacar(PILA);
			pasarACola(&aux, COLA);
			if(*PILA != NULL && ((*PILA)->content == B_OPERATOR || (*PILA)->content == U_FUNCTION))
				headPrecedence = (*PILA)->symbol;
		}
	}
	// luego copio la OP actual a la pila
	apilar(B_OPERATOR, op, PILA);
}

static double getNumber(const char *str, unsigned int *i)
{
	char buf[128];
	int pos=0;

	while (isNumber(str[pos]))
	{
		buf[pos] = str[pos];
		pos++;
		(*i)++;
	}
	buf[pos] = '\0';

	return atof(buf);
}

static int isNumber(char c)
{
	if (c >= '0' && c <= '9')
		return 1; // es numero
	else if (c == '.' || c == ',')
		return 2; // es coma
	else
		return 0; // no es numero
}

static int isBOperation(char c)
{
	switch(c)
	{
		case '+': return SUM;
		case '-': return SUBSTRACTION;
		case '*': return MULTIPLICATION;
		case '/': return DIVISION;
		case '^': return POWER;
		default : return 0;
	}
}

static int isUOperation(char c)
{
	switch(c)
	{
		case '!': return FACTORIAL;
		case '-': return MINUS;
	}
	return 0;
}

static int isUFunction(const char *inf, unsigned int *i)
{
	char buf[8] = "";
	int func = 0;
	size_t sz = 0;

	while(sz < 4 && inf[sz] != '\0' && isAlpha(inf[sz]))
	{
		buf[sz] = inf[sz];
		sz++;
		(*i)++;

		if(sz == 2)
		{
			buf[sz] = '\0';
			if(!strcmp(buf, "ln"))
				func = LN;
		}
		else if(sz == 3)
		{
			buf[sz] = '\0';
			if(!strcmp(buf, "log"))
				func = LOG;
			else if(!strcmp(buf, "sin"))
				func = SIN;
			else if(!strcmp(buf, "cos"))
				func = COS;
			else if(!strcmp(buf, "tan"))
				func = TAN;
		}
		else if(sz == 4)
		{
			buf[sz] = '\0';
			if(!strcmp(buf, "sqrt"))
				func = SQRT;
		}

		if(func != 0)
			break;
	}
	if(sz != 0)
		(*i)--;

	return func;
}

static int isBFunction(const char *inf, unsigned int *i)
{
	char buf[8] = "";
	int func = 0;
	size_t sz = 0;

	while(sz < 4 && inf[sz] != '\0' && isAlpha(inf[sz]))
	{
		buf[sz] = inf[sz];
		sz++;
		(*i)++;

		if(sz == 3)
		{
			buf[sz] = '\0';
			if(!strcmp(buf, "pow"))
				func = POWER;
		}
		else if(sz == 4)
		{
			buf[sz] = '\0';
			if(!strcmp(buf, "root"))
				func = ROOT;
		}

		if(func != 0)
			break;
	}
	if(sz != 0)
		(*i)--;

	return func;
}

static int isConstant(const char *inf, unsigned int *i, double *num, double ans)
{
	char buf[8] = "";
	size_t sz = 0;

	while(sz < 3 && inf[sz] != '\0' && isAlpha(inf[sz]))
	{
		buf[sz] = inf[sz];
		sz++;

		if(sz == 1)
		{
			buf[sz] = '\0';
			if(!strcmp(buf, "e")) {
				*num = M_E;
				(*i)+=sz;
				return 1;
			}
			else if(!strcmp(buf, "π")) {
				*num = M_PI;
				(*i)+=sz;
				return 1;
			}
		}
		if(sz == 2)
		{
			buf[sz] = '\0';
			if(!strcasecmp(buf, "pi")) {
				*num = M_PI;
				(*i)+=sz;
				return 1;
			}
		}
		else if(sz == 3)
		{
			buf[sz] = '\0';
			if(!strcasecmp(buf, "ans")) {
				*num = ans;
				(*i)+=sz;
				return 1;
			}
		}
	}

	return 0;
}

static int isParenthesis(char c)
{
	if (c == '(')
		return PARENTHESIS_OPEN;

	if(c == ')')
		return PARENTHESIS_CLOSE;

	return 0;
}

double solvePostfix(node_t** Cola, int *errorFlag)
{
	node_t* Pila = NULL;
	node_t* aux1 = NULL;
	node_t* aux2 = NULL;
	node_t* op = NULL;
	node_t* res = NULL;
	double resu = 0.0;

	while(*Cola != NULL)
	{
		if((*Cola)->content == B_OPERATOR || (*Cola)->content == B_FUNCTION)
		{
			op = sacar(Cola);
			aux2 = sacar(&Pila);
			aux1 = sacar(&Pila);
			res = solve_binary(aux1, aux2, &op, errorFlag);
			pasarAPila(&res, &Pila);
		}
		else if((*Cola)->content == U_FUNCTION || (*Cola)->content == U_OPERATOR)
		{
			op = sacar(Cola);
			aux1 = sacar(&Pila);
			res = solve_unary(aux1, &op, errorFlag);
			pasarAPila(&res, &Pila);
		}
		else
		{
			pasarAPila(Cola, &Pila);
		}
		if(*errorFlag != E_NO)
			break;
	}
	if(Pila != NULL && *errorFlag == E_NO)
		resu = Pila->number;
	vaciar(&Pila);
	vaciar(Cola);
	return resu;
}


// basic binary operations
node_t* solve_binary(node_t* n1, node_t* n2, node_t** operation, int *errorFlag)
{
	static double (*opPtr[])(double, double) = {sumar, restar, multiplicar, dividir, pow, root, pow};
	node_t* result = *operation; // reuse of this object

	if(n1 == NULL || n2 == NULL || *operation == NULL)
		return NULL;

	if(checkMath_binary(n1->number, (*operation)->symbol, n2->number) != E_NO)
		*errorFlag = E_MATH;
	else
	{
		int operator = (*operation)->symbol - SUM;
		result->number = (*opPtr[operator]) (n1->number, n2->number);
		result->content = NUMBER;
	}
	eliminarNodo(&n1);
	eliminarNodo(&n2);

	return result;
}

node_t* solve_unary (node_t* n, node_t** operation, int *errorFlag)
{
	static double (*opPtr[])(double) = {factorial, negate, sqrt, log, ln, sin, cos, tan};
	node_t* result = *operation; // reuse of this object

	if(n == NULL || *operation == NULL)
		return NULL;

	if(checkMath_unary(n->number, (*operation)->symbol) != E_NO)
		*errorFlag = E_MATH;
	else
	{
		int operator = (*operation)->symbol - FACTORIAL;
		result->number = (*opPtr[operator]) (n->number);
		result->content = NUMBER;
	}
	eliminarNodo(&n);

	return result;
}

static int checkMath_binary(double n1, int op, double n2)
{
	switch (op)
	{
	case DIVISION:
		if(n2 == 0.0)
			return E_MATH;
		break;
	case POWER:
	// exp real y base negativa, resultado imaginario
	// 0^0 no definido
		if(((n2 - (int)n2 != 0.0) && (n1 < 0)) || \
			(n1 == 0.0 && n2 == 0.0) )
			return E_MATH;
		break;
	default:
		break;
	}
	return E_NO;
}

static int checkMath_unary(double n, int op)
{
	switch(op)
	{
	case FACTORIAL:
		if(n - (int)n != 0.0)
			return E_MATH;
	default:
		break;
	}
	return E_NO;
}


static const char *getSymbol(symbol_t symbol)
{
	switch(symbol)
	{
		case SUM: return "+";
		case SUBSTRACTION: return "-";
		case MULTIPLICATION: return "*";
		case DIVISION: return "/";
		case POWER: return "^";
		case FACTORIAL: return "!";
		case MINUS: return "(-)";
		case ROOT: return "root";
		case SQRT: return "sqrt";
		case LOG: return "log";
		case LN: return "ln";
		case SIN: return "sin";
		case COS: return "cos";
		case TAN: return "tan";
		case POW: return "pow";
		case PARENTHESIS_OPEN: return "(";
		case PARENTHESIS_CLOSE: return ")";
	}
	return "";
}

void printNodes(node_t* N)
{
	fputs("Cadena de nodos-> ", stdout);
	while (N != NULL)
	{
		if(N->content == NUMBER)
			printf("[%.*g]", 4, N->number);
		else
			printf("[%s]", getSymbol(N->symbol));

		N = N->next;
	}
	puts("");
	return;
}
