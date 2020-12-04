#include "uls.h"

int		uls_isname_toolong(char *path) {
	char	**arr;
	int		i;

	arr = mx_strsplit(path, '/');
	i = 0;
	while (arr[i])
	{
		if (mx_strlen(arr[i]) > LS_NAME_SIZE)
		{
			mx_arr_free(&arr);
			return (1);
		}
		i++;
	}
	mx_arr_free(&arr);
	return (0);
}
