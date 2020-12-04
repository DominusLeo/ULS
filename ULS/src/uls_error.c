#include "uls.h"

void		uls_out_error(t_lspath *path)
{
	PI = 0;
	while (path->e_path[PI])
	{
		if (uls_isname_toolong(path->e_path[PI]))
		{
			if (path->flags[G_BIG])
				mx_printstr(LS_RED);
			mx_putstr_fd("ls: ", 2);
			mx_putstr_fd(path->e_path[PI], 2);
			mx_putstr_fd(": File name too long\n", 2);
		}
		else
		{
			if (path->flags[G_BIG])
				mx_printstr(LS_YELLOW);
			mx_putstr_fd("ls: ", 2);
			mx_putstr_fd(path->e_path[PI], 2);
			mx_putstr_fd(": No such file or directory\n", 2);
		}
		PI++;
	}
	if (path->flags[G_BIG])
		mx_printstr(LS_NORMAL);
}

void	uls_print_permision_error(char *path) {
	if (mx_strrchr(path, '/')) {
		mx_putstr_fd("ls: ", 2);
		mx_putstr_fd(mx_strrchr(path, '/') + 1, 2);
		mx_putstr_fd(": Permission denied\n", 2);
	}
	else {
		mx_putstr_fd("ls: ", 2);
		mx_putstr_fd(path, 2);
		mx_putstr_fd(": Permission denied\n", 2);
	}
}
