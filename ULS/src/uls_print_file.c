#include "uls.h"

void		uls_show_link(char *path)
{
	char buf[LS_NAME_SIZE + 1];

	mx_bzero(buf, LS_NAME_SIZE + 1);
	readlink(path, buf, LS_NAME_SIZE);
    ft_printf(" -> %s", buf);//printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

static void	uls_print_time(struct stat stat_buf)
{
	char	*t;
	time_t	local_time;

	local_time = time(0);
	local_time -= stat_buf.st_mtime;
	t = mx_strdup(ctime(&stat_buf.st_mtime));
	if ((local_time * (((local_time) > 0) * 2 - 1)) > 15770000)
        ft_printf(" %3.3s %2.2s  %4.4s", &t[4], &t[8], &t[20]);//printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	else
        ft_printf(" %3.3s %2.2s %5.5s", &t[4], &t[8], &t[11]);//printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	free(t);
}

static void	uls_l(char *path, char *name, int *width)
{
	struct stat		stat_buf;
	char			*mode;

	lstat(path, &stat_buf);
	uls_get_mode(&mode, path, stat_buf.st_mode);
    ft_printf("%s %*d %*s  %*s  %*jd",
	mode,
	width[0], stat_buf.st_nlink,
	width[1], getpwuid(stat_buf.st_uid)->pw_name,
	width[2], getgrgid(stat_buf.st_gid)->gr_name,
	width[3], (intmax_t)stat_buf.st_size);//printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	uls_print_time(stat_buf);
	ft_printf(" %s", name);//printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (S_ISLNK(stat_buf.st_mode))
		uls_show_link(path);
	write(1, "\n", 1);
	free(mode);
}

void		uls_print_file(char *path, char *name, char *flg, int *width)
{
	if (flg[L_MINI])
		uls_l(path, name, width);
	else
        ft_printf("%s\n", name);//printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
