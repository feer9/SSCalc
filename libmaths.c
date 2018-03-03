#include "libmaths.h"

/*	Agregar una func promediar(n1,n2,...) indefinidos
	agregar funcion operar(n1, OPERACION, n2) con puntero a funcion (o en el orden q quieras)
*/

double sumar(double a, double b)
{
	return (a+b);
}

double restar(double a, double b)
{
	return (a-b);
}

double multiplicar(double a, double b)
{
	return (a*b);
}

double dividir(double a, double b)
{
	if(b != 0.0)
		return (a/b);
	else
	{
		perror("Error, división por cero\n");
		return(0);
	}
}

double areaCirculo(double radio)
{
	return (M_PI * radio * radio);
}

int max(int a, int b)
{
	return (a > b ? a:b);
}

int min(int a, int b)
{
	return (a < b ? a:b);
}

// recibe un vector de numeros
// devuelve la posicion del mayor
int mayor(int* v, size_t n)
{
	unsigned int i;
	int num_mayor = v[0];
	int may = 0;
	for(i=1; i<n; i++)
	{
		if(v[i] > num_mayor)
		{
			num_mayor = v[i];
			may = (int) i;
		}
	}
	return may;
}

// recibe un vector de numeros
// devuelve la posicion del menor
int menor(int* v, size_t n)
{
	unsigned int i;
	int num_menor = v[0];
	int men = 0;
	for(i=1; i<n; i++)
	{
		if(v[i] < num_menor)
		{
			num_menor = v[i];
			men = (int) i;
		}
	}
	return men;
}

double prom(int* vec, size_t n)
{
	int unsigned i;
	double suma = 0;

	for(i=0; i<n; i++)
		suma += vec[i];

	return (suma / (double) n);
}

unsigned long int factorial(int num)
{
	unsigned long int factorial = 1;

	if(num < 0)
		factorial = 0;

	while(num > 1)
	{
		factorial *= num;
		num--;
	}
	return factorial;
}

unsigned long int fibonacci(int num)
{
	unsigned long int an, an1 = 1, an2 = 1;
	int i;

	if(num <= 0)
		an = 0;
	else if(num < 3)
		an = 1;
	else
	{
		for(i=3; i<=num; i++)
		{
			an = an1 + an2;
			an2 = an1;
			an1 = an;
		}
	}
	return an;
}


void quicksort(int *ve, size_t n)
{
	qs(ve, 0, (int)n-1);
}

void qs(int *v, int ext_izq, int ext_der)
{
	int izq = ext_izq;
	int der = ext_der;
	int pivote = *(v+(izq+der)/2);

	do{
		while(*(v + izq) < pivote && (izq < ext_der)) izq++;
		while(*(v + der) > pivote && (der > ext_izq)) der--;
		if(izq <= der)
		{
			swap((v+izq), (v+der));
			izq++;
			der--;
		}
	} while(izq < der);

	if(ext_izq < der) qs(v, ext_izq, der);
	if(ext_der > izq) qs(v, izq, ext_der);
}

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

double mediana(int *vec, size_t n)
{
	return cuartil(2, vec, n);
}

double cuartil(int cuartil, int *vec, size_t n)
{
	int i;		// parte entera
	double d;	// parte decimal
	double q=0;	// cuartil

	if(n > 0)
	{
		quicksort(vec, n);

		if(cuartil == 2)
		{
			if(n%2) //impar
				q = (double) vec[n/2];
			else    //par
				q = (double) (vec[n/2 - 1] + vec[n/2]) / 2.0;
		}
		else if(cuartil == 1 || cuartil == 3)
		{
			i = (int)     cuartil * (n+1) / 4;
			d = (double) (cuartil * (n+1) % 4) / 4.0;
			q = vec[i-1] + d * (vec[i] - vec[i-1]);
		}

		return q;
	}
	else
		return vec[0];
}

double dEstandar(int *vec, size_t n)
{
	unsigned int i;
	double promedio, sumatoria = 0.0;

	// calculo el promedio o media aritmÃ©tica (xÌ„)
	promedio = prom(vec, n);
//	printf("\nMedia aritmÃ©tica (xÌ„): %lf \n", promedio);

	// calculo la sumatoria de los cuadrados de la diferencia entre
	// cada elemento del vector y el promedio de ellos ( sum [(Xi - Xprom ) ^ 2] )
	for(i=0; i<n; i++)
		sumatoria += pow(vec[i] - promedio, 2);

	// retorno la raiz de la inversa de la cantidad de elementos menos uno,
	// por la sumatoria calculada. Esto es, la desviacion estandar del vector.
	return sqrt(sumatoria / (n - 1));
}

int prodEscalar(int *vec1, int *vec2, size_t tamV1, size_t tamV2)
{
	unsigned int ciclo = 0;
	int res = 0;

	while(ciclo < tamV1 || ciclo < tamV2)
	{
		res += (*(vec1 + ciclo) * *(vec2 + ciclo));
		ciclo++;
	}
	return res;
}

void burbujeo(int *v, int max)
{
	int ciclos, i;
	for(ciclos = 1; ciclos < max; ciclos++)
		for(i = 0; i < (max - ciclos); i++)
			if(*(v + i) > *(v + i + 1))
				swap((v + i), (v + i + 1));
}

int busqueda(int *v, int M, int D)
{
	int i = 0;
	while(*(v+i) != D && i < M) i++;
	if(*(v+i) == D) return i;
		else return -1;
}

int buscaBin(int *v, int tam, int D)
{
	int izq = 0;
	int der = tam - 1;
	int pivote = (der + izq) / 2;
	while(*(v + pivote) != D && (izq <= der))
	{
		if(*(v + pivote) < D) 	izq = pivote + 1;
			else		der = pivote - 1;
		pivote = (izq + der) / 2;
	}
	if(*(v + pivote) == D) 	return pivote;
		else		return -1;
}


double ipow(double b, double e)
{
	if (e < 0) return 1/ipow_aux(b, (int) -e);
	else return ipow_aux(b, (int) e);
}

double ipow_aux(double b, int e)
{
	if (e == 0)
		return 1;
	else
	{
		double x = ipow_aux(b, e/2);
		if (e%2)
			return x*x*b;
		else
			return x*x;
	}
}
/*
double ipow(double x,int i)
{
	double r = 1.0;

	if(x == 0 && i == 0)
		return 0;
	else if(i == 0)
		return 1;
	else if(i < 0)
	{
		i *= -1;
		for(;i>0;i--) r *= x;
		return 1.0 / r;
	}

	for(;i>0;i--) r *= x;
	return r;
}
*/
double pow(double b, double ex)
{
	double result;
	double PolyExp[GRADMACLAURINSERIES + 1];

	MacLaurinExp(PolyExp, GRADMACLAURINSERIES);
	ex *= ln(b);
	if (ex > 0)
		result = pow_aux((int)ex);
	else
		result = 1.0 / pow_aux((int)-ex);

	result *= evalPoly(PolyExp, ex - (int)ex);
	return result;
}

double *MacLaurinExp(double *Poly, int grad) // grad = lenght Poly - 1
{
	int i;
	Poly[0] = 1.0;
	for (i = 1; i <= grad; ++i)
		Poly[i] = (double) Poly[i-1]/i;
	return Poly;
}

double evalPoly(double *Poly, double x)
{
	int i;
	double result = 0;
	for (i = GRADMACLAURINSERIES; i >= 0; --i)
		result = result*x + Poly[i];
	return result;
}

double pow_aux(int ex)
{
	if (ex == 0)
		return 1;
	else
		return M_E*pow_aux(ex-1);
}

double sqrt(double x)
{
	return pow(x, 0.5);
}

double rootOf(double x, double n)
{
	return pow(x, 1.0/n);
}

double logarithm(int b,double n)
{
	double val = 0;
	int i,accurate = 10,reps=0;
	while(n != 1 && accurate>=0)
	{
		for(i=0;n>=b;i++)
			n /= b;
		n = ipow(n,10);
		val = 10*(val+i);
		accurate--; reps++;
	}
	return (double) val/ipow(10,reps);
}

double ln(double num)
{
	return logarithm(10, num) / logarithm(10, M_E);
}

double log(double num)
{
	return logarithm(10, num);
}
