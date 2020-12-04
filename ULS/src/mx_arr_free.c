#include "uls.h"

void	mx_arr_free(char ***arr) {
	int len;

	len = mx_arrlen(*arr);
	while (--len >= 0)
		free((*arr)[len]);
	free(*arr);
}
