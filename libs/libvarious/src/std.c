#include "std.h"

double atof(const char *s)
{
	int signo = 1, pos_coma = -1;
	double num=0.0;
	size_t i = 0, n = strlen(s);

	if(s[i] == '-')
	{
		signo = -1;
		i++;
	}

	for(; i < n ; i++)
	{
		if(s[i] >= '0' && s[i] <= '9')			// es un numero
		{
			if(pos_coma < 0)					// parte entera
			{
				num *= 10;						// desplazo mi coma un lugar a la derecha
				num += (double) (s[i] - '0');	// sumo el num actual
			}
			else								// parte decimal
			// sumo el numero actual con su peso decimal como 10^-(pos a derecha de la coma)
				num += (double) (s[i] - '0') * ipow(10.0, -(i - pos_coma));
		}
		// si hay una coma (y es la primera q veo)
		else if ((s[i] == '.' || s[i] == ',') && pos_coma < 0)
			pos_coma = i;
		// si hay otra cosa en el string, termino ahi
		else
			break;
	}

	return (num * signo);
}

int atoi(const char *s)
{
	int signo = 1, num = 0;
	size_t i=0, n = strlen(s);

	if(s[i] == '-')
	{
		signo = -1;
		i++;
	}

	for(; i < n ; i++)
	{
		if(s[i] < '0' || s[i] > '9')
			break;
		num *= 10;
		num += (s[i] - '0');
	}

	return (num * signo);
}
