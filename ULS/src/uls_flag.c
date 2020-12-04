#include "uls.h"

int	ls_filter1(t_lspath *path, int c)
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

void	uls_rev_bigr_flag(t_uls *uls, char *flag) {
	LI = mx_arrlen(uls->file_path);
	while (--LI >= 0) {
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

void	uls_bigr_flag(t_uls *uls, char *flag) {
	if (flag[R_MINI]) {
		uls_rev_bigr_flag(uls, flag);
		return ;
	}
	LI = 0;
	while (uls->file_path[LI]) {
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
