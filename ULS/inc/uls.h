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
