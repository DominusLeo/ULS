#include "uls.h"

int		uls_isdir(char *path) {
	DIR *directory;

	if (!(directory = opendir(path)))
		return (0);
	closedir(directory);
	return (1);
}

int		uls_isfile(char *path) {
	struct stat file_stat;

	if (lstat(path, &file_stat) < 0)
		return (0);
	return (1);
}
