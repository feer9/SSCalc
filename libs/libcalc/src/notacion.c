#include "notacion.h"


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
	c = isOperation(str[i]);
	if((c >= MULTIPLICACION && c <= POTENCIA) || c == PARENTESIS_C)
		return E_SINTAXIS;
	
	while(i < tama && parentesis >= 0)
	{
		if (c >= SUMA && c <= POTENCIA) {
			ops_consec++;
			comas = 0;
		}
		else {
			ops_consec = 0;
			esNum = isNumber(str[i]);
			if(esNum == 2) { // coma
				comas++;
				if(comas > 1)
					return E_SINTAXIS;
			}
			else if(!esNum && !c)
				return E_SINTAXIS;
		}

		if(ops_consec > 1 && (c != SUMA && c != RESTA))
		// despues de un operador, solo puede haber un + o un -
			return E_SINTAXIS;
		if(ops_consec > 2)
			return E_SINTAXIS;

		if (c == PARENTESIS_A)
			parentesis++;
		else if (c == PARENTESIS_C)
			parentesis--;

		c = isOperation(str[++i]);
	}

	return (parentesis + ops_consec == 0) ? E_NO : E_SINTAXIS;
}

node_t* infixToPostfix(const char* inf, double ans)
{
	unsigned int i=0, k;
	int op; // actual operation
	int precedenciaOp=0, caso, negativo = NO;
	char str_aux[256];
	char cima;
	node_t* PILA = NULL;
	node_t* COLA = NULL;
	node_t* nodo_aux = NULL;
	const size_t tama = strlen(inf); // tamaño de la expresion

	// compruebo si la expresion empieza con un negativo
	op = isOperation(inf[i]);
	if(op == RESTA)
	{
//		negativo = SI;   no sirve por ejemplo si pongo -2^2 la caga
		acolarNumero(0.0, &COLA);
		apilar(OPERADOR, '-', &PILA);
		i++;
		op = isOperation(inf[i]);
	}
	else if (op == SUMA)
	// si algun boludo puso un + adelante del primer numero
	{
		i++;
		op = isOperation(inf[i]);
	}


	while (i < tama)
	{
		if(op)
			caso = op;

		else if(isNumber(inf[i]))
			caso=NUMERO;

		else
			caso = -1; // ninguno


		switch(caso)
		{
		// si se abre un parentesis, lo meto en la pila
		case PARENTESIS_A:
			apilar(SIMBOLO, inf[i], &PILA);
			break;

		// al encontrar un parentesis que se cierra ')',
		// mando los elementos de la pila a la cola,
		// hasta encontrar un parentesis que se abra. Este ultimo se elimina.
		case PARENTESIS_C:
			nodo_aux = sacar(&PILA);
			while (nodo_aux != NULL && \
					(nodo_aux->Content == NUMERO || nodo_aux->Content == OPERADOR || \
					 (nodo_aux->Content == SIMBOLO && nodo_aux->Operator != '(' ) ) )
			{
				pasarACola(&nodo_aux, &COLA);
				nodo_aux = sacar(&PILA);
			}
			if(nodo_aux->Content == SIMBOLO && nodo_aux->Symbol == '(')
				free(nodo_aux);
			break;


			// si es +, -, *, / ó ^
		case POTENCIA:						precedenciaOp += 2; // 2+2+1=5
		case MULTIPLICACION: case DIVISION:	precedenciaOp += 2; //   2+1=3
		case SUMA: case RESTA:				precedenciaOp += 1; //     1=1

			/*  para suma y resta (1 y 2) si en la pila tengo otras operaciones consecutivas, las tengo que pasar a la cola
			 *  para mult y divis (3 y 4) si en la pila tengo mult, div o pot las tengo que pasar a la cola
			 *  para potencia (5) solo si en la pila hay otras potencias, las paso a la cola
			 */

			if(PILA != NULL && PILA->Content == OPERADOR)
			{
				cima = isOperation(PILA->Operator);

				while (PILA != NULL && ( cima >= precedenciaOp && cima <= POTENCIA ))
				{	// los mando a la cola
					nodo_aux = sacar(&PILA);
					pasarACola(&nodo_aux, &COLA);
					if(PILA != NULL && PILA->Content == OPERADOR)
						cima = isOperation(PILA->Operator);
				}
			}
			// luego copio la OP actual a la pila
			apilar(OPERADOR, inf[i], &PILA);

			precedenciaOp=0;
			break;

		// si el caracter es un numero
		case NUMERO:

			k = 0;
			// me fijo si es negativo
			if(negativo)
			{
				negativo = OK;
				str_aux[k] = '-';
				k++;
			}
			// lo copio en str_aux
			do
			{
				str_aux[k] = inf[i];
				k++;
				i++;
			}
			while (isNumber(inf[i]));
			str_aux[k] = '\0';
			// lo agrego a la cola
			acolarNumero(atof(str_aux), &COLA);
			// y como despues voy a hacer un i++
			i--;
			break;

		default:
			break;

		} // switch

		i++;

		// si lo que sigue a algo que no sea un numero, es un signo menos, se le aplica al siguiente numero
		op = isOperation(inf[i]);
		if ((caso != NUMERO && caso != PARENTESIS_C) && \
				(op == SUMA || op == RESTA))
		{
			i++;
			if (op == RESTA)
				negativo = SI;
			op = isOperation(inf[i]);
		}
	} // while

	// por ultimo, todo lo que quede en la pila se pasa a la cola
	while (PILA != NULL)
	{
		nodo_aux = sacar(&PILA);
		pasarACola(&nodo_aux, &COLA);
	}

	return COLA;
}

int isNumber(char c)
{
	if (c >= '0' && c <= '9')
		return 1; // es numero
	else if (c == '.' || c == ',')
		return 2; // es coma
	else
		return 0; // no es numero
}

int isOperation(char c)
{
	switch(c)
	{
		case '+': return SUMA;
		case '-': return RESTA;
		case '*': return MULTIPLICACION;
		case '/': return DIVISION;
		case '^': return POTENCIA;
		case '(': return PARENTESIS_A;
		case ')': return PARENTESIS_C;
		default : return 0;
	}
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
		if((*Cola)->Content == OPERADOR)
		{
			op = sacar(Cola);
			aux2 = sacar(&Pila);
			aux1 = sacar(&Pila);
			res = solve(aux1, aux2, &op, errorFlag);
			pasarAPila(&res, &Pila);
		}
		else
		{
			pasarAPila(Cola, &Pila);
		}
		if(*errorFlag != E_NO)
			break;
	}
	if(Pila != NULL)
		resu = Pila->Number;
	vaciar(&Pila);
	vaciar(Cola);
	return resu;
}

node_t* solve(node_t* n1, node_t* n2, node_t** operacion, int *errorFlag)
{
	static double (*pOperacion[])(double, double) = {sumar, restar, multiplicar, dividir, pow};
	node_t* resultado;

	if(n1 == NULL || n2 == NULL || operacion == NULL)
		return NULL;

	if(checkMath(n1->Number, (*operacion)->Operator, n2->Number) != E_NO)
		*errorFlag = E_MATH;
	else
	{
		int Operator = isOperation((*operacion)->Operator) - 1;
		resultado = *operacion;
		//resultado->Number = (*fResolver[Operator]) (n1->Number,n2->Number);
		resultado->Number = operar (n1->Number, n2->Number,
									pOperacion[Operator]);
		resultado->Content = NUMERO;
	}
	eliminarNodo(&n1);
	eliminarNodo(&n2);

	return resultado;
}

int checkMath(double n1, char op, double n2)
{
	switch (op)
	{
	case '/':
		if(n2 == 0.0)
			return E_MATH;
		break;
	case '^':
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

void printNodes(node_t* N)
{
	fputs("Cadena de nodos-> ", stdout);
	while (N != NULL)
	{
		if(N->Content == NUMERO)
			printf("[%.*g]", 4, N->Number);
		else
			printf("[%c]", N->Symbol);

		N = N->next;
	}
	puts("");
	return;
}
