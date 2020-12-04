#include "uls.h"

static void	uls_time_sort_algo(char ***arr, struct stat	*file_stat, int j)
{
	struct timespec	tmp;

	tmp = file_stat[j].st_mtimespec;
	file_stat[j].st_mtimespec = file_stat[j + 1].st_mtimespec;
	file_stat[j + 1].st_mtimespec = tmp;
	uls_sort(arr, j);
}

static void	uls_time_sort_if(char ***arr, struct stat *file_stat, int j)
{
	if ((file_stat[j].st_mtimespec.tv_sec)
		< (file_stat[j + 1].st_mtimespec.tv_sec))
	{
		uls_time_sort_algo(arr, file_stat, j);
	}
	else if (file_stat[j].st_mtimespec.tv_sec
		== file_stat[j + 1].st_mtimespec.tv_sec
		&& file_stat[j].st_mtimespec.tv_nsec
		== file_stat[j + 1].st_mtimespec.tv_nsec)
	{
		if (mx_strcmp((*arr)[j], (*arr)[j + 1]) > 0)
			uls_time_sort_algo(arr, file_stat, j);
	}
	else if (file_stat[j].st_mtimespec.tv_sec
		== file_stat[j + 1].st_mtimespec.tv_sec
		&& file_stat[j].st_mtimespec.tv_nsec
		< file_stat[j + 1].st_mtimespec.tv_nsec)
	{
		uls_time_sort_algo(arr, file_stat, j);
	}
}

void		uls_time_sort(char ***arr, int i, int j)
{
	int			len;
	struct stat	*file_stat;

	len = mx_arrlen(*arr);
	if (len < 2)
		return ;
	file_stat = uls_get_stat(*arr);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < (len - 1))
		{
			uls_time_sort_if(arr, file_stat, j);
			j++;
		}
		i++;
	}
	free(file_stat);
}

void		uls_base_sort(char ***arr)
{
	int		i;
	int		j;
	int		len;

	len = mx_arrlen(*arr);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (mx_strcmp((*arr)[j], (*arr)[j + 1]) > 0)
				uls_sort(arr, j);
			j++;
		}
		i++;
	}
}

void		uls_len_sort(char ***arr) {
	int		i;
	int		j;
	int		len;
	size_t	size;
	size_t	size1;

	len = mx_arrlen(*arr);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			size = mx_strlen((*arr)[j]);
			size1 = mx_strlen((*arr)[j + 1]);
			if (size > size1)
				uls_sort(arr, j);
			else if (size == size1)
				if (mx_strcmp((*arr)[j], (*arr)[j + 1]) > 0)
					uls_sort(arr, j);
			j++;
		}
		i++;
	}
}
