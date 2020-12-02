#include "libmx.h"

void mx_del_strarr(char ***arr) {
    char **arr2;

    if (!arr)
        return;
    arr2 = *arr;
    for( ; *arr2; arr2++)
        mx_strdel(arr2);
    free(*arr);
    *arr = NULL;
}
