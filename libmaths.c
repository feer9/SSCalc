#include "libmaths.h"

/*	Agregar pow() y sqrt() EN C
	y a modo didÃ¡ctico, una func promediar(n1,n2,...) indefinidos
	funcion operar(n1, OPERACION, n2) con puntero a funcion (o en el orden q quieras)
*/

double areaCirculo(double radio)
{
    return (PI * radio * radio);
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
#if 0
double dEstandar(int *vec, size_t tam)
{
	int i;
	double promedio, sumatoria = 0.0;

//	calculo el promedio o media aritmÃ©tica (xÌ„)
	promedio = prom(vec, n);
//	printf("\nMedia aritmÃ©tica (xÌ„): %lf \n", promedio);

	for(i=0; i<tam; i++)
		sumatoria += pow(vec[i] - promedio, 2); // calculo la sumatoria de los cuadrados de la diferencia entre cada elemento del vector y el promedio de ellos ( sum (Xi - Xprom ) ^ 2 )

	return sqrt(sumatoria / (tam - 1)); // retorno la raiz de la inversa de la cantidad de elementos menos uno, por la sumatoria calculada. Esto es, la desviacion estandar del vector.
}
#endif

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

#if 1
double pow(double a, double b)
{
  // calculate approximation with fraction of the exponent
  int e = (int) b;
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)((b - e) * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;

  // exponentiation by squaring with the exponent's integer part
  // double r = u.d makes everything much slower, not sure why
  double r = 1.0;
  while (e) {
    if (e & 1) {
      r *= a;
    }
    a *= a;
    e >>= 1;
  }

  return r * u.d;
}
#else
double pow(double a, double b) {
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;
  return u.d;
}
#endif
