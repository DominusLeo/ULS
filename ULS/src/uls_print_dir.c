#include "uls.h"

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
