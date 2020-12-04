#include "uls.h"

void		uls_mem(t_lspath *path, int f_len, int d_len, int e_len) {
	path->files = (char **)malloc(sizeof(char *) * f_len + 1);
	path->files[f_len] = NULL;
	path->dirs = (char **)malloc(sizeof(char *) * d_len + 1);
	path->dirs[d_len] = NULL;
	path->e_path = (char **)malloc(sizeof(char *) * e_len + 1);
	path->e_path[e_len] = NULL;
}

int uls_get_args(t_lspath *path, char **argv) {
    path->files = NULL;
    path->dirs = NULL;
    path->e_path = NULL;
    if ((PJ = uls_get_flags(path, argv)) > 0) {
        mx_putstr_fd("ls: illegal option -- ", 2);
        mx_putchar_fd(PJ, 2);
        mx_putstr_fd("\nusage: ./ls [-AGRSalrtvy1] [file ...]\n", 2);
        return (0);
    }
    uls_get_path(path, argv);
    //sort;
    return (1);
}

int *uls_get_width(struct stat *stat_buf, int size) {
    int *width;
    int i;

    width = (int *)malloc(sizeof(int) * 4);
    mx_bzero(width, sizeof(int) * 4);
    i = 0;
    while(i < size) {
        width[0] = MAX(width[0], mx_nbrlen(stat_buf[i].st_nlink));
        width[1] = MAX(width[1],
		(int)mx_strlen(getpwuid(stat_buf[i].st_uid)->pw_name));
		width[2] = MAX(width[2],
		(int)mx_strlen(getgrgid(stat_buf[i].st_gid)->gr_name));
		width[3] = MAX(width[3], mx_nbrlen(stat_buf[i].st_size));
		i++;
    }
    return (width);
}

struct stat *uls_get_stat(char **path) {
    struct stat *file_stat;
    int i;
    int j;

    j = mx_arrlen(path);
    file_stat = (struct stat *)malloc(sizeof(struct stat) * j);
    i = 0;
    while (i < j) {
        lstat(path[i], &file_stat[i]); //?
        i++;
    }
    return (file_stat);
}

void uls_get_path(t_lspath *path, char **argv) {
	int f_len;
	int d_len;
	int e_len;

	uls_get_mem(path, argv);
	f_len = 0;
	d_len = 0;
	e_len = 0;
	while (argv[PI]) {
		if ((uls_isdir(argv[PI]) || errno == 13))
			path->dirs[d_len++] = mx_strdup(argv[PI]);
		else if (uls_isfile(argv[PI]))
			path->files[f_len++] = mx_strdup(argv[PI]);
		else
			path->e_path[e_len++] = mx_strdup(argv[PI]);
		PI++;
	}
}

void		uls_get_mem(t_lspath *path, char **argv) {
	int f_len;
	int d_len;
	int e_len;

	if (argv[PI] && !mx_strcmp(argv[PI], "--"))
		PI++;
	f_len = 0;
	d_len = 0;
	e_len = 0;
	PJ = PI;
	while (argv[PJ]) {
		if (uls_isdir(argv[PJ]) || errno == 13)
			d_len++;
		else if (uls_isfile(argv[PJ]))
			f_len++;
		else
			e_len++;
		PJ++;
	}
	uls_mem(path, f_len, d_len, e_len);
}
