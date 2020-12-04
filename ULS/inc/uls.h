#pragma once

#include "../libmx/inc/libmx.h"

//======== includes ========//
#include <fcntl.h>
#include <limits.h>
#include <malloc/malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>

#include <uuid/uuid.h>

# define LS_NORMAL		"\x1B[0m"
# define LS_RED			"\x1B[31m"
# define LS_GREEN		"\x1B[32m"
# define LS_YELLOW		"\x1B[33m"
# define LS_BLUE		"\x1B[34m"
# define LS_MAGENTA		"\x1B[35m"
# define LS_CYAN		"\x1B[36m"

# define LS_NAME_SIZE	255
# define LS_FLAG_SIZE	10
# define LS_MODE_SIZE	11

# define MAX(a, b) (a > b ? a : b)

# define R_BIG			0
# define R_MINI			1
# define A_MINI			2
# define L_MINI			3
# define T_MINI			4
# define G_BIG			5
# define V_MINI			6
# define Y_MINI			7
# define S_BIG			8
# define A_BIG			9

# define LI uls->i
# define LJ uls->j
# define PI path->i
# define PJ path->j

typedef struct			s_uls {
	char				**file_path;
	struct stat			*file_stat;
	int					*width;
	int					i;
	int					j;
}						t_uls;

typedef struct			s_lspath {
	char				flags[LS_FLAG_SIZE + 1];
	char				**files;
	char				**dirs;
	char				**e_path;
	int					i;
	int					j;
}                       t_lspath;

void mx_bzero(void *s, size_t n);
size_t	mx_arrlen(char **arr);
void	mx_arr_free(char ***arr);
long long int mx_nbrlen(long long int nb);
void mx_putstr_fd(char const *s, int fd);
void mx_putchar_fd(char c, int fd);
void		uls_len_sort(char ***arr);
void		uls_base_sort(char ***arr);
void		uls_time_sort(char ***arr, int i, int j);
void		uls_sort(char ***arr, int index);
struct stat *uls_get_stat(char **path);
void		uls_print_file(char *path, char *name, char *flg, int *width);
char	*mx_strrchr(const char *s, int c);
int			uls_get_mode(char **line, char *path, mode_t mode);

