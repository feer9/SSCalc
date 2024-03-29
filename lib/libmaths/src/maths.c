#include "maths.h"

// recibe un vector de numeros
// devuelve la posicion del mayor
int mayor(size_t n, const int* v)
{
	size_t i;
	int num_mayor = v[0];
	int pos_mayor = 0;
	for(i=1; i<n; i++)
	{
		if(v[i] > num_mayor)
		{
			num_mayor = v[i];
			pos_mayor = (int) i;
		}
	}
	return pos_mayor;
}

// recibe un vector de numeros
// devuelve la posicion del menor
int menor(size_t n, const int* v)
{
	size_t i;
	int num_menor = v[0];
	int pos_menor = 0;
	for(i=1; i<n; i++)
	{
		if(v[i] < num_menor)
		{
			num_menor = v[i];
			pos_menor = (int) i;
		}
	}
	return pos_menor;
}

// Recibe como primer argumento el número de argumentos
// seguido por numeros a promediar
double promediar (size_t n, ...)
{
	va_list args;
	long int sum = 0;

	va_start(args, n);

	for(int i=0; i<(int)n; i++)
		sum += va_arg(args, int);
	
	va_end(args);
	
	return (double) sum / n;
}

double promediarVector(size_t n, const int* vec)
{
	long int sum = 0;

	for(size_t i=0; i<n; i++)
		sum += vec[i];

	return (double) sum / n;
}

//unsigned long int factorial(int num)
double factorial(double num)
{
	double factorial = 1;

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
	unsigned long int an = 1, an1 = 1, an2 = 1;
	int i;

	if(num <= 0)
		an = 0;

	for(i=3; i<=num; i++)
	{
		an = an1 + an2;
		an2 = an1;
		an1 = an;
	}
	return an;
}


void quicksort(size_t n, int *ve)
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

double mediana(size_t n, int *vec)
{
	return cuartil(2, n, vec);
}

double cuartil(int cuartil, size_t n, int *vec)
{
	int i;		// parte entera
	double d;	// parte decimal
	double q=0;	// cuartil

	if(n > 0)
	{
		quicksort(n, vec);

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

double dEstandar(size_t n, int *vec)
{
	unsigned int i;
	double promedio, sumatoria = 0.0;

	// calculo el promedio o media aritmÃ©tica (xÌ„)
	promedio = promediarVector(n, vec);
//	printf("\nMedia aritmÃ©tica (xÌ„): %lf \n", promedio);

	// calculo la sumatoria de los cuadrados de la diferencia entre
	// cada elemento del vector y el promedio de ellos ( sum [(Xi - Xprom ) ^ 2] )
	for(i=0; i<n; i++)
		sumatoria += pow(vec[i] - promedio, 2);

	// retorno la raiz de la inversa de la cantidad de elementos menos uno,
	// por la sumatoria calculada. Esto es, la desviacion estandar del vector.
	return sqrt(sumatoria / (n - 1));
}

int prodEscalar(size_t tamV1, const int *vec1, size_t tamV2, const int *vec2)
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

int busqueda(const int *v, int M, int D)
{
	int i = 0;
	while(v[i] != D && i < M)
		i++;
	if(v[i] == D)
		return i;
	else
		return -1;
}

int buscaBin(const int *v, int tam, int D)
{
	int izq = 0;
	int der = tam - 1;
	int pivote = (der + izq) / 2;
	while(v[pivote] != D && (izq <= der))
	{
		if(v[pivote] < D)
			izq = pivote + 1;
		else
			der = pivote - 1;
		pivote = (izq + der) / 2;
	}
	if(v[pivote] == D)
		return pivote;
	else
		return -1;
}

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
	return (a/b);
}

double pow(double b, double ex)
{
	double result;
	static double PolyExp[GRADMACLAURINSERIES + 1];
	static char polyInit = 0;

	if(ex - (int)ex == 0.0) // exponente entero
		return ipow(b, ex);

	if(!polyInit)
	{
		// TODO: see __attribute__((constructor))
		// https://code-examples.net/en/q/12593e
		polyInit = 1;
		MacLaurinExp(PolyExp, GRADMACLAURINSERIES);
	}
	ex *= log(b);

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

double evalPoly(const double *Poly, double x)
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

double ipow(double b, double e)
{
	if (e < 0) return 1.0/ipow_aux(b, (int) -e);
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

double sqrt(double x)
{
	return pow(x, 0.5);
}

double root(double x, double n)
{
	return pow(x, 1.0/n);
}

double logarithm(int b, double n)
{
	if (b <= 1 || n <= 0)
		return 0;
	else if (n < 1)
		return -logarithm_aux(b, 1.0/n);
	else
		return logarithm_aux(b, n);
}

double logarithm_aux(int b, double n)
{
	double val = 0;
	int i,accurate = 30,reps=0;

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

// logarithm in base e
inline double log(double num)
{
	return logarithm(10, num) / M_LOG10E;
}

// logarithm in base 10
inline double log10(double num)
{
	return logarithm(10, num);
}

long double remquol(long double x, long double y, int *quo)
{
	long double div = x/y;
	long double resto = div - (int) div;

	if(resto > 0.5)
		*quo = (int) div + 1;
	else if(resto <= -0.5)
		*quo = (int) div - 1;
	else
		*quo = (int) div;

	return x - (*quo) * y;
}

// x in degrees
double sin(double _x)
{
	long double x = _x;
	long double res, term, x2, t1;
	int phase;

	x = remquol(x, 90, &phase);
	if (phase & 1)
		x = 90 - x;

	x = x * M_PI_L / 180; // convert x to radians
	x2 = x * x;           // pre-compute x^2

	// compute the sine series: x - x^3/3! + x^5/5! ...
	res = term = x;   // the first term is x
	for (int n = 1; n < SINE_DEPTH; n += 4) {
		// to reduce precision loss, compute 2 terms for each iteration
		t1 = term * x2 / ((n + 1) * (n + 2));
		term = t1 * x2 / ((n + 3) * (n + 4));
		// update the result with the difference of the terms
		res += term - t1;
	}
	if (phase & 2)
		res = -res;

	return (double) res;
}
// todo: maybe implement horner's method?

extern inline double cos(double x)
{
	return sin(90.0 - x);
}

extern inline double tan(double x)
{
	return sin(x) / sin(90.0 - x);
}

extern inline double abs_(double x)
{
	return x < 0.0 ? -x : x;
}
