#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
	unsigned int i;
	double pow_n = n;

	if(pow == 0 || n == 1)
	    return 1;
	for (i = 0; i < (pow - 1); i++)
		n = (double)n * pow_n;
	return n;
}
