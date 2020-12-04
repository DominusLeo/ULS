#include "uls.h"

int uls_get_args(t_lspath *path, char **argv) {
    path->files = NULL;
    path->dirs = NULL;
    path->e_path = NULL;
    if ((PJ = uls_get_flags(path, argv)) > 0) {
        
    }
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

void uls_output(t_uls *uls, char *flag) {
    if (flag[L_MINI]) {
        if (uls->file_stat)
            free(uls->file_stat);
        uls->file_stat = uls_get_stat(uls->file_path);
        uls->width = uls_get_width(uls->file_stat, mx_arrlen(uls->file_path));
    }
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

void uls_print_dir(char *path, char *flag) {
    t_uls uls;
    uls.file_stat = NULL;
    uls.width = NULL;
    if (!(uls_readdir(&uls, path, flag)))
        return ;
    if (flag[V_MINI])
        mx_arrlen(uls.file_path);
    // if(flag[S_BIG])
    uls_output(&uls, flag);
    mx_arr_free(&uls.file_path);
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
    }
    return 0;
}
