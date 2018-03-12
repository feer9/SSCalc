#ifndef LIBMATHS_H_INCLUDED
#define LIBMATHS_H_INCLUDED

#include <stdio.h>
//#include <stdlib.h>
#include <sys/types.h>
//#include <stddef.h>
//#include <stdint.h>

/* Some useful constants.									*/
# define M_E		2.7182818284590452354	/* e			*/
# define M_LOG2E	1.4426950408889634074	/* log_2 e		*/
# define M_LOG10E	0.43429448190325182765	/* log_10 e		*/
# define M_LN2		0.69314718055994530942	/* log_e 2		*/
# define M_LN10		2.30258509299404568402	/* log_e 10		*/
# define M_PI		3.14159265358979323846	/* pi			*/
# define M_PI_2		1.57079632679489661923	/* pi/2			*/
# define M_PI_4		0.78539816339744830962	/* pi/4			*/
# define M_1_PI		0.31830988618379067154	/* 1/pi			*/
# define M_2_PI		0.63661977236758134308	/* 2/pi			*/
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi)	*/
# define M_SQRT2	1.41421356237309504880	/* sqrt(2)		*/
# define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2)	*/

#define GRADMACLAURINSERIES 20

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

double sumar(double a, double b);
double restar(double a, double b);
double multiplicar(double a, double b);
double dividir(double a, double b);
double areaCirculo(double radio);
int max(int a, int b);
int min(int a, int b);
int mayor(int *v, size_t n);
int menor(int *v, size_t n);
double prom(int *vec, size_t n);
unsigned long int factorial(int num);
unsigned long int fibonacci(int num);
void swap(int *a, int *b);
void quicksort(int *ve, size_t n);
void qs(int *v, int ext_izq, int ext_der);
void burbujeo(int *v, int max);
int busqueda(int *v, int M, int D);
int buscaBin(int *v, int tam, int D);
double cuartil(int cuartil, int *vec, size_t n);
double mediana(int *vec, size_t n);
double dEstandar(int *vec, size_t n);
int prodEscalar(int *vec1, int *vec2, size_t tamV1, size_t tamV2);
double ipow(double b, double e);
double ipow_aux(double b, int e);
double pow_aux(int ex);
double pow(double b, double ex);
double *MacLaurinExp(double *Poly, int grad);
double evalPoly(double *Poly, double x);
double sqrt(double x);
double rootOf(double x, double n);
double log(double num);
double ln(double num);
double logarithm(int b,double n);



#endif // LIBMATHS_H_INCLUDED
