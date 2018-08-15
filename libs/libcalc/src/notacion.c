#include "notacion.h"


// Función que verifica una expresión matemática.
// Devuelve 0 si está todo bien
int checkExpr(const char* str)
{
	int c;
	int i = 0;
	int ops_consec = 0;
	int parentesis = 0;
	int tama;

	tama = (int) strlen(str);
	c = esOp(str[i]);
	if(c >= 3 && c <= 5)
		return 1;
	else while(i < tama && parentesis >= 0)
	{
		if (c >= 1 && c <=5)
			ops_consec++;
		else
			ops_consec = 0;

		if(ops_consec > 1 && (c != 1 && c != 2)) // despues de un operador, solo puede haber un + o un -
			return 1;
		if(ops_consec > 2)
			return 1;

		if ( !c && !esNum(str[i]) ) // no es operador y ni operando
			return 1;

		if (c == 6)      // (
			parentesis++;
		else if (c == 7) // )
			parentesis--;

		i++;
		c = esOp(str[i]);
	}

	return parentesis + ops_consec;
}

nodo* infijaAPostfija(const char* inf, double ans)
{
	unsigned int i=0, k;
	int op; // OP actual
	int tipoDeOp=0, caso = -1, negativo = NO;
	char aux[256];
	char primer_elem = 'n';
	nodo* PILA = NULL;
	nodo* COLA = NULL;
	nodo* n_aux = NULL;
	const size_t tama = strlen(inf); // tamaño de la expresion

	while(inf[i] == ' ') {
        i++;
	}

	// compruebo si la expresion empieza con un negativo
	op = esOp(inf[i]);
	if(op == RESTA)
	{
//		negativo = SI;   no sirve por ejemplo si pongo -2^2 la caga
		acolarNumero(0.0, &COLA);
		apilar(OPERADOR, '-', &PILA);
		i++;
		op = esOp(inf[i]);
	}
	else if (op == SUMA)
	// si algun boludo puso un + adelante del primer numero
	{
		i++;
		op = esOp(inf[i]);
	}


	while (i < tama)
	{
		if(!op)
		{
			if(esNum(inf[i]))
				caso=NUMERO;
		}
		else
			caso = op;


		switch(caso)
		{
		// si se abre un parentesis, lo meto en la pila
		case PARENTESIS_A:
			apilar(SIMBOLO, inf[i], &PILA);
			break;

		// al encontrar un parentesis que se cierra ')', mando los elementos de la pila a la cadena,
		// hasta encontrar un parentesis que se abra. Este ultimo se elimina.
		case PARENTESIS_C:
			n_aux = sacar(&PILA);
			while (n_aux != NULL && \
					(n_aux->contenido == NUMERO || n_aux->contenido == OPERADOR || \
					 (n_aux->contenido == SIMBOLO && n_aux->operador != '(' ) ) )
			{
				pasarACola(&n_aux, &COLA);
				n_aux = sacar(&PILA);
			}
			if(n_aux->contenido == SIMBOLO && n_aux->simbolo == '(')
				free(n_aux);
			break;


			// si es +, -, *, / ó ^
		case POTENCIA:						tipoDeOp += 2; // =5
		case MULTIPLICACION: case DIVISION:	tipoDeOp += 2; // =3
		case SUMA: case RESTA:				tipoDeOp += 1; // =1

			/*  para suma y resta (1 y 2) si en la pila tengo otras operaciones consecutivas, las tengo que pasar a la cola
			 *  para mult y divis (3 y 4) si en la pila tengo mult, div o pot las tengo que pasar a la cola
			 *  para potencia (5) solo si en la pila hay otras potencias, las paso a la cola
			 */

			if(PILA != NULL && PILA->contenido == OPERADOR)
			{
				primer_elem = esOp(PILA->operador);

				while (PILA != NULL && ( primer_elem >= tipoDeOp && primer_elem <= POTENCIA ))
				{	// los mando a la cola
					n_aux = sacar(&PILA);
					pasarACola(&n_aux, &COLA);
					if(PILA != NULL && PILA->contenido == OPERADOR)
						primer_elem = esOp(PILA->operador);
				}
			}
			// luego copio la OP actual a la pila
			apilar(OPERADOR, inf[i], &PILA);

			tipoDeOp=0;
			break;

		// si el caracter es un numero
		case NUMERO:

			k = 0;
			// me fijo si es negativo
			if(negativo)
			{
				negativo = OK;
				aux[k] = '-';
				k++;
			}
			// lo copio en aux
			do
			{
				aux[k] = inf[i];
				k++;
				i++;
			}
			while (esNum(inf[i]));
			aux[k] = '\0';
			// lo agrego a la cola
			acolarNumero(atof(aux), &COLA);
			// y como despues voy a hacer un i++
			i--;
			break;

		default:
			while(inf[i] == ' ') {
				i++;
			}
			break;

		} // switch

		i++;
		// si lo que sigue a algo que no sea un numero, es un signo menos, se le aplica al siguiente numero
		op = esOp(inf[i]);
		if ((caso != NUMERO && caso != PARENTESIS_C) && \
				(op == SUMA || op == RESTA))
		{
			i++;
			if (op == RESTA)
				negativo = SI;
			op = esOp(inf[i]);
		}
		caso = -1; // ninguno
	} // while

	// por ultimo, todo lo que quede en la pila se pasa a la cola
	while (PILA != NULL)
	{
		n_aux = sacar(&PILA);
		pasarACola(&n_aux, &COLA);
	}

	return COLA;
}

int esNum(char c)
{
	if ((c >= '0' && c <= '9') || c == '.' || c == ',')
		return 1; // es numero (o coma)
	else
		return 0; // no es numero
}

int esOp(char c)
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
		case ' ': return ESPACIO;
		default : return 0;
	}
}

double resolverPostfija(nodo** Cola, int *errorFlag)
{
	nodo* Pila = NULL;
	nodo* aux1 = NULL;
	nodo* aux2 = NULL;
	nodo* op = NULL;
	nodo* res = NULL;
	double resu = 0.0;

	while(*Cola != NULL)
	{
		if((*Cola)->contenido == OPERADOR)
		{
			op = sacar(Cola);
			aux2 = sacar(&Pila);
			aux1 = sacar(&Pila);
			res = resolver(aux1, aux2, &op, errorFlag);
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
		resu = Pila->numero;
	vaciar(&Pila);
	vaciar(Cola);
	return resu;
}

nodo* resolver(nodo* n1, nodo* n2, nodo** op, int *errorFlag)
{
	double (*fResolver[])(double, double) = {sumar, restar, multiplicar, dividir, pow};

	if(n1 == NULL || n2 == NULL || op == NULL)
		return NULL;

	if(checkMath(n1->numero, (*op)->operador, n2->numero))
		*errorFlag = E_MATH;
	else
	{
		(*op)->numero = (*fResolver[esOp((*op)->operador) - 1]) (n1->numero,n2->numero);
		(*op)->contenido = NUMERO;
	}
	eliminar(&n1);
	eliminar(&n2);

	return *op;
}

int checkMath(double n1, char op, double n2)
{
	switch (op)
	{
	case '/':
		if(n2 == 0.0)
			return 1;
		break;
	case '^':
	// exp real y base negativa, resultado imaginario
	// 0^0 no definido
		if(((n2 - (int)n2 != 0.0) && (n1 < 0)) || \
			(n1 == 0.0 && n2 == 0.0) )				
			return 1;
		break;
	default:
		break;
	}
	return 0;
}

void mostrar(nodo* N)
{
	fputs("Cadena de nodos-> ", stdout);
	while (N != NULL)
	{
		if(N->contenido == NUMERO)
			printf("[%.*g]", 4, N->numero);
		else
			printf("[%c]", N->simbolo);

		N = N->sig;
	}
	puts("");
	return;
}
