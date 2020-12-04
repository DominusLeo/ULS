#include "uls.h"

void		uls_print_total(t_uls *uls) {
	long long int t;

	t = 0;
	LI = 0;
	while (uls->file_path[LI])
	{
		t += uls->file_stat[LI].st_blocks;
		LI++;
	}
	ft_printf("total %lld\n", t);//printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void	uls_rev_output(t_uls *uls, char *flag)
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

void	uls_output(t_uls *uls, char *flag) {
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
