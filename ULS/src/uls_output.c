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

int max_name_len(char **files) {
    int max_len = -260;

    for (int i = 0; files[i]; i++)
        if (mx_strlen(files[i]) > max_len)
            max_len = mx_strlen(files[i]);
    return max_len;
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
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    LI = 0;
    t_for_matrix *fil = NULL;
    fil = (t_for_matrix *)malloc(sizeof(t_for_matrix) * 100);
    fil->files = malloc(sizeof(char **) * 100);
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    fil->term_weight = w.ws_col;

    for (int i = 0; uls->file_path[LI]; i++, LI++)
        fil->files[i] = mx_strrchr(uls->file_path[LI], '/') + 1;

    fil->print_format = fil->term_weight / max_name_len(fil->files) + 4;
    fil->strings = (int ) mx_arrlen(fil->files) /
            (fil->term_weight / max_name_len(fil->files) - 1) + 1;

//    ft_printf("weight term = %d\n", fil->term_weight);
//    ft_printf("ammount files = %d\n", mx_arrlen(fil->files));
//    ft_printf("max_name = %d\n", max_name_len(fil->files));
//    printf("format in printf = %d\n", fil->print_format);
//    printf("amm strings = %d\n", fil->strings);
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    LI = 0;
    while (uls->file_path[LI])
	{
        if (flag[G_BIG])
            uls_color(LI);
        uls_print_file(uls->file_path[LI], fil->files[LI], flag, uls->width);
        LI++;
    }
    //we need work here
    for (int i = 0; i < fil->strings;) {
        for (size_t j = i++; j < mx_arrlen(fil->files); j += fil->strings) {
//            char *ws = "";
//            for (int form = 0; form < fil->print_format; form++) {
//            ws = mx_strjoin(ws, " ");
//            }
            ft_printf("%-16s\t", fil->files[j]);
        }
        ft_printf("\n");
    }
    //________________________________________________________________________
    if (flag[G_BIG])
		mx_printstr(LS_NORMAL);
}
