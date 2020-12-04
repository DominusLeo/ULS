#include "uls.h"

struct stat *uls_get_stat(char **path);
void uls_print_dir(char *path, char *flag);
void	uls_print_permision_error(char *path);
void		uls_print_total(t_uls *uls);
static void	uls_rev_output(t_uls *uls, char *flag);
void		uls_color(int c);

int		uls_isname_toolong(char *path)
{
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

int		uls_isfile(char *path) {
	struct stat file_stat;

	if (lstat(path, &file_stat) < 0)
		return (0);
	return (1);
}

int		uls_isdir(char *path) {
	DIR *directory;

	if (!(directory = opendir(path)))
		return (0);
	closedir(directory);
	return (1);
}

static void		uls_mem(t_lspath *path, int f_len, int d_len, int e_len) {
	path->files = (char **)malloc(sizeof(char *) * f_len + 1);
	path->files[f_len] = NULL;
	path->dirs = (char **)malloc(sizeof(char *) * d_len + 1);
	path->dirs[d_len] = NULL;
	path->e_path = (char **)malloc(sizeof(char *) * e_len + 1);
	path->e_path[e_len] = NULL;
}

static void		uls_get_mem(t_lspath *path, char **argv) {
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

static int	ls_filter1(t_lspath *path, int c)
{
	if (c == 'R')
		path->flags[R_BIG] = 'R';
	else if (c == 'r')
		path->flags[R_MINI] = 'r';
	else if (c == 'a')
		path->flags[A_MINI] = 'a';
	else if (c == 'l')
		path->flags[L_MINI] = 'l';
	else if (c == 't')
		path->flags[T_MINI] = 't';
	else if (c == 'G')
		path->flags[G_BIG] = 'G';
	else if (c == 'v')
		path->flags[V_MINI] = 'v';
	else if (c == 'y')
		path->flags[Y_MINI] = 'y';
	else if (c == 'S')
		path->flags[S_BIG] = 'S';
	else if (c == 'A')
		path->flags[A_BIG] = 'A';
	else if (c == '1')
		path->flags[L_MINI] = '\0';
	else
		return (c);
	return (0);
}

int	uls_get_flags(t_lspath *path, char **argv) {
	PI = 0;
	while (argv[PI] && argv[PI][0] == '-') {
		PJ = 1;
		if (!argv[PI][PJ])
			return (0);
		if (argv[PI][PJ] == '-' && !argv[PI][PJ + 1])
			return (0);
		while (argv[PI][PJ]) {
			if (ls_filter1(path, argv[PI][PJ]) > 0)
				return ((int)argv[PI][PJ]);
			PJ++;
		}
		PI++;
	}
	return (0);
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

int uls_get_args(t_lspath *path, char **argv) {
    path->files = NULL;
    path->dirs = NULL;
    path->e_path = NULL;
    if ((PJ = uls_get_flags(path, argv)) > 0) {
        mx_putstr_fd("ls: illegal option -- ", 2);
        mx_putchar_fd(PJ, 2);
        mx_putstr_fd("\nusage: ./mx_ls [-AGRSalrtvy1] [file ...]\n", 2);
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

static void	uls_output(t_uls *uls, char *flag)
{
	if (flag[L_MINI])
	{
		if (uls->file_stat)
			free(uls->file_stat);
		uls->file_stat = uls_get_stat(uls->file_path);
		uls->width = uls_get_width(uls->file_stat, mx_arrlen(uls->file_path));
	}
	if (flag[R_MINI])
	{
		uls_rev_output(uls, flag);
		return ;
	}
	if (flag[L_MINI] && uls->file_path[0])
		uls_print_total(uls);
	LI = 0;
	while (uls->file_path[LI])
	{
		if (flag[G_BIG])
			uls_color(LI);
		uls_print_file(uls->file_path[LI],
		(mx_strrchr(uls->file_path[LI], '/') + 1), flag, uls->width);
		LI++;
	}
	if (flag[G_BIG])
		mx_printstr(LS_NORMAL);
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

void		uls_print_total(t_uls *uls){
	long long int t;

	t = 0;
	LI = 0;
	while (uls->file_path[LI])
	{
		t += uls->file_stat[LI].st_blocks;
		LI++;
	}
	printf("total %lld\n", t);
}

void		uls_color(int c)
{
	c %= 7;
	if (c == 0)
		mx_printstr(LS_RED);
	else if (c == 1)
		mx_printstr(LS_YELLOW);
	else if (c == 2)
		mx_printstr(LS_GREEN);
	else if (c == 3)
		mx_printstr(LS_CYAN);
	else if (c == 4)
		mx_printstr(LS_BLUE);
	else if (c == 5)
		mx_printstr(LS_MAGENTA);
	else if (c == 6)
		mx_printstr(LS_NORMAL);
}

static void	uls_rev_output(t_uls *uls, char *flag)
{
	if (flag[L_MINI] && uls->file_path[0])
		uls_print_total(uls);
	LI = mx_arrlen(uls->file_path);
	while (--LI >= 0)
	{
		if (flag[G_BIG])
			uls_color(LI);
		uls_print_file(uls->file_path[LI],
		(mx_strrchr(uls->file_path[LI], '/') + 1), flag, uls->width);
	}
	if (flag[G_BIG])
		mx_printstr(LS_NORMAL);
}

static void	uls_rev_bigr_flag(t_uls *uls, char *flag)
{
	LI = mx_arrlen(uls->file_path);
	while (--LI >= 0)
	{
		if ((uls_isdir(uls->file_path[LI])
			&& mx_strcmp((mx_strrchr(uls->file_path[LI], '/') + 1), ".")
			&& mx_strcmp((mx_strrchr(uls->file_path[LI], '/') + 1), "..")))
		{
			printf("\n%s:\n", uls->file_path[LI]);
			uls_print_dir(uls->file_path[LI], flag);
		}
		else if (errno == 13)
		{
			printf("\n%s:\n", uls->file_path[LI]);
			uls_print_permision_error(uls->file_path[LI]);
		}
	}
}

static void	uls_bigr_flag(t_uls *uls, char *flag)
{
	if (flag[R_MINI])
	{
		uls_rev_bigr_flag(uls, flag);
		return ;
	}
	LI = 0;
	while (uls->file_path[LI])
	{
		if ((uls_isdir(uls->file_path[LI])
			&& mx_strcmp((mx_strrchr(uls->file_path[LI], '/') + 1), ".")
			&& mx_strcmp((mx_strrchr(uls->file_path[LI], '/') + 1), "..")))
		{
			printf("\n%s:\n", uls->file_path[LI]);
			uls_print_dir(uls->file_path[LI], flag);
		}
		else if (errno == 13)
		{
			printf("\n%s:\n", uls->file_path[LI]);
			uls_print_permision_error(uls->file_path[LI]);
		}
		LI++;
	}
}

void uls_print_dir(char *path, char *flag) {
    t_uls uls;
    uls.file_stat = NULL;
    uls.width = NULL;
    if (!(uls_readdir(&uls, path, flag)))
        return ;
    if (flag[V_MINI])
        mx_arrlen(uls.file_path);
    if(flag[S_BIG])
        uls_big_s_sort(&uls.file_path);
    else if (flag[Y_MINI])
        uls_len_sort(&uls.file_path);
    else if (flag[T_MINI])
        uls_time_sort(&uls.file_path, 0, 0);
    else
        uls_base_sort(&uls.file_path);
    uls_output(&uls, flag);
    if (flag[R_BIG])
        uls_bigr_flag(&uls, flag);
    if (uls.file_stat)
		free(uls.file_stat);
    if (uls.width)
        free(uls.width);
    mx_arr_free(&uls.file_path);
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

static void		uls_out_error(t_lspath *path)
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

void	uls_print_permision_error(char *path)
{
	if (mx_strrchr(path, '/'))
	{
		mx_putstr_fd("ls: ", 2);
		mx_putstr_fd(mx_strrchr(path, '/') + 1, 2);
		mx_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		mx_putstr_fd("ls: ", 2);
		mx_putstr_fd(path, 2);
		mx_putstr_fd(": Permission denied\n", 2);
	}
}

static void		uls_lobi(t_lspath *path)
{
	uls_out_error(path);
	uls_out_file(path);
	PI = 0;
	if (path->dirs[0] && path->files[0])
		write(1, "\n", 1);
	if (path->dirs[0] && (path->files[0] || path->e_path[0] || path->dirs[1]))
		printf("%s:\n", path->dirs[0]);
	while (path->dirs[PI])
	{
		uls_isdir(path->dirs[PI]);
		if (errno == 13)
			uls_print_permision_error(path->dirs[PI]);
		else
			uls_print_dir(path->dirs[PI], path->flags);
		PI++;
		if (path->dirs[PI])
			printf("\n%s:\n", path->dirs[PI]);
	}
}

int main(int argc, char **argv) {
    t_lspath path;

    (void)argv;
    mx_bzero(path.flags, LS_FLAG_SIZE + 1); // bzero - заменить на memset
    if (argc == 1) {
        uls_print_dir(".", path.flags);
    }
    else {
        if (!(uls_get_args(&path, argv + 1)))
            return (1);
        if (!path.e_path[0] && !path.files[0] && !path.dirs[0])
			uls_print_dir(".", path.flags);
        else
			uls_lobi(&path);
		mx_arr_free(&path.files);
		mx_arr_free(&path.dirs);
		mx_arr_free(&path.e_path);
    }
    return 0;
}
