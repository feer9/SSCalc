#ifndef LIBMATHS_H_INCLUDED
#define LIBMATHS_H_INCLUDED

//#include <stdlib.h>
#include <sys/types.h>
//#include <stddef.h>
//#include <stdint.h>

#define PI 3.1415926535897932
#define GRADMACLAURINSERIES 20
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

double areaCirculo(double radio);
int max(int, int);
int min(int, int);
int mayor(int *v, size_t n);
int menor(int *v, size_t n);
double prom(int *vec, size_t n);
unsigned long int factorial(int num);
unsigned long int fibonacci(int num);
void swap(int *, int *);
void quicksort(int *, size_t);
void qs(int *, int, int);
void burbujeo(int*, int);
int busqueda(int*, int, int);
int buscaBin(int*, int, int);
double cuartil(int cuartil, int *vec, size_t n);
double mediana(int*, size_t n);
//double dEstandar(int *vec, size_t tam);
int prodEscalar(int *vec1, int *vec2, size_t tamV1, size_t tamV2);
double pow(double a, double b);



#endif // LIBMATHS_H_INCLUDED
