#include "maths.h"

int main()
{
	double b,e;
	while(1) {
		#if 0
		printf("num: ");
		scanf("%lf",&a);
		printf("fibonacci de %d: %d\n",(int) a, fibonacci((int) a));
		printf("factorial de %d: %d\n",(int) a, factorial((int) a));
		printf("raiz cuadrada de %lf: %.10lf\n",a, sqrt(a));
		printf("\n");
		#endif
		#if 1
		printf("base: ");
		scanf("%lf",&b);
		printf("exp: ");
		scanf("%lf",&e);
		printf("\n%lf^%lf = %g\n",b,e, pow(b,e));
		printf("\n(%lf)rootOf(%lf) = %.20lf\n",e,b, root(b,e));
		printf("\nsqrt(%lf) = %.20lf\n",b, sqrt(b));
		#endif
		#if 0
		printf("\nbase: ");
		scanf("%lf",&b);
		printf("num: ");
		scanf("%lf",&e);
		printf("\nlog_%lf(%lf) = %.15lf\n",b,e, logarithm(b,e));
		#endif
	}
	return 0;
}