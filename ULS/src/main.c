#include "uls.h"

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
    // if (flag[V_MINI])
    //     mx_arrlen(uls.file_path);
    // if(flag[S_BIG])

}

int main(int argc, char **argv) {
    t_lspath pth;

    (void)argv;
    mx_bzero(pth.flags, LS_FLAG_SIZE + 1); // bzero - заменить на memset
    if (argc == 1) {
        uls_print_dir(".", pth.flags);
    }
    return 0;
}
