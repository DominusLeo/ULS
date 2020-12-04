#include "uls.h"

long long int mx_nbrlen(long long int nb) {
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0) {
		nb /= 10;
		i++;
	}
	return (i);
}
