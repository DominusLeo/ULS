#include "uls.h"

size_t	mx_arrlen(char **arr) {
	size_t len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
