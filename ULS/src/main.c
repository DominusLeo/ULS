#include "uls.h"
#include <stdio.h>

void		uls_sort(char ***arr, int index)
{
	char	*buf;

	buf = mx_strdup((*arr)[index]);
	free((*arr)[index]);
	(*arr)[index] = mx_strdup((*arr)[index + 1]);
	free((*arr)[index + 1]);
	(*arr)[index + 1] = mx_strdup(buf);
	free(buf);
}

static void	uls_big_s_sort_algo(char ***arr, struct stat	*file_stat, int j)
{
	intmax_t	tmp;

	tmp = file_stat[j].st_size;
	file_stat[j].st_size = file_stat[j + 1].st_size;
	file_stat[j + 1].st_size = tmp;
	uls_sort(arr, j);
}

void		uls_big_s_sort(char ***arr) {
	int			len;
	int			i;
	int			j;
	struct stat	*file_stat;

	len = mx_arrlen(*arr);
	if (len < 2)
		return ;
	file_stat = uls_get_stat(*arr);
	i = 0;
	while (i < len) {
		j = 0;
		while (j < (len - 1)) {
			if (file_stat[j].st_size < file_stat[j + 1].st_size)
				uls_big_s_sort_algo(arr, file_stat, j);
			else if (file_stat[j].st_size == file_stat[j + 1].st_size)
				if (mx_strcmp((*arr)[j], (*arr)[j + 1]) > 0)
					uls_big_s_sort_algo(arr, file_stat, j);
			j++;
		}
		i++;
	}
	free(file_stat);
}

void uls_file_count(t_uls *uls, char *flag, char *path) {
    struct dirent *dir;
    DIR *directory;
    int len = 0;

    directory = opendir(path);
    dir = readdir(directory);
    while (dir) {
        if (flag[A_MINI] || (flag[A_BIG] 
        && mx_strcmp(dir->d_name, ".") 
        && mx_strcmp(dir->d_name, "..")) || dir->d_name[0] != '.')
        len++;
        dir = readdir(directory);
    }
    closedir(directory);
    uls->file_path = (char **)malloc(sizeof(char *) * len + 1);
    uls->file_path[len] = NULL;
}

int uls_readdir(t_uls *uls, char *path, char *flag) {
    struct dirent *dir;
    DIR *directory;
    char *buf = NULL;

    directory = opendir(path);
    dir = readdir(directory);
    if (!dir) {
        closedir(directory);
        return (0);
    }
    uls_file_count(uls, flag, path);
    buf = mx_strjoin(path, "/");
	uls->i = 0;
    while (dir) {
		if (flag[A_MINI] || (flag[A_BIG]
			&& mx_strcmp(dir->d_name, ".")
			&& mx_strcmp(dir->d_name, "..")) || dir->d_name[0] != '.')
			uls->file_path[uls->i++] = mx_strjoin(buf, dir->d_name);
		dir = readdir(directory);
	}
	closedir(directory);
	free(buf);
	return (1);
}

static void		uls_out_file_l(t_lspath *path)
{
	int			*width;
	struct stat	*stat_buf;

	if (!path->files[0])
		return ;
	stat_buf = uls_get_stat(path->files);
	width = uls_get_width(stat_buf, mx_arrlen(path->files));
	if (path->flags[G_BIG])
		mx_printstr(LS_CYAN);
	if (path->flags[R_MINI])
	{
		PI = mx_arrlen(path->files);
		while (--PI >= 0)
			uls_print_file(path->files[PI], path->files[PI], path->flags, width);
	}
	else
	{
		PI = 0;
		while (path->files[PI])
			uls_print_file(path->files[PI], path->files[PI++], path->flags, width);
	}
	if (path->flags[G_BIG])
		mx_printstr(LS_NORMAL);
	free(width);
	free(stat_buf);
}

static void		uls_out_file(t_lspath *path)
{
	if (path->flags[V_MINI] && path->files[0])
		mx_arrlen(path->files);
	if (path->flags[L_MINI])
	{
		uls_out_file_l(path);
		return ;
	}
	if (path->flags[G_BIG])
		mx_printstr(LS_CYAN);
	if (path->flags[R_MINI])
	{
		PI = mx_arrlen(path->files);
		while (--PI >= 0)
			uls_print_file(path->files[PI], path->files[PI], path->flags, NULL);
	}
	else
	{
		PI = 0;
		while (path->files[PI])
			uls_print_file(path->files[PI], path->files[PI++], path->flags, NULL);
	}
	if (path->flags[G_BIG])
		mx_printstr(LS_NORMAL);
}

static void		uls_lobi(t_lspath *path)
{
	uls_out_error(path);
	uls_out_file(path);
	PI = 0;
	if (path->dirs[0] && path->files[0])
		write(1, "\n", 1);
	if (path->dirs[0] && (path->files[0] || path->e_path[0] || path->dirs[1]))
		ft_printf("%s:\n", path->dirs[0]);
	while (path->dirs[PI])
	{
		uls_isdir(path->dirs[PI]);
		if (errno == 13)
			uls_print_permision_error(path->dirs[PI]);
		else
			uls_print_dir(path->dirs[PI], path->flags);
		PI++;
		if (path->dirs[PI])
			ft_printf("\n%s:\n", path->dirs[PI]);
	}
}

int main(int argc, char **argv) {
    t_lspath path;

    (void)argv;
    //wide of terminal window
    t_for_matrix *fil = NULL;
    fil = (t_for_matrix *)malloc(sizeof(t_for_matrix));
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    fil->term_weight = (int )malloc(sizeof(int) * 4);
    fil->term_weight = w.ws_col;
    ft_printf("weight term = %d\n", fil->term_weight);
    //______

    mx_bzero(path.flags, LS_FLAG_SIZE + 1); // bzero - заменить на memset
    if (argc == 1) {
        uls_print_dir(".", path.flags);
    }
    else {
        if (!(uls_get_args(&path, argv + 1))) {
            return (1);
        }
        if (!path.e_path[0] && !path.files[0] && !path.dirs[0]) {
            uls_print_dir(".", path.flags);
        }
        else {
            uls_lobi(&path);
        }
        mx_arr_free(&path.files);
        mx_arr_free(&path.dirs);
        mx_arr_free(&path.e_path);
    }
//    system("leaks -q uls");
    return 0;
}
