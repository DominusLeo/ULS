#include "libmx.h"

static void mx_swap_str(char **s1, char **s2) {
    char *tmp = *s1;

    *s1 = *s2;
    *s2 = tmp;
}

static int count_move(char **arr, int *left, int *right, int *pos) {
    int res = 0;

    if (*pos == *right)
        --(*right);
    if (*pos == *left)
        ++(*left);
    else {
        ++res;
        mx_swap_str(&arr[*pos], &arr[*left]);
    }
    if (*left < *right)
        res += mx_quicksort(arr, *left, *right);
    return res;
}

int mx_quicksort(char **arr, int left, int right) {
    int pos = left;
    int len;

    if (!arr)
        return -1;
    len = mx_strlen(arr[left]);
    for (int beg = left, end = right; beg < end; --end) {
        if (len > mx_strlen(arr[end])) {
            pos = end;
            for (++beg; beg < end; ++beg) {
                if (len < mx_strlen(arr[beg])) {
                    pos = beg;
                    break;
                }
            }
        }
    }
    return count_move(arr, &left, &right, &pos);
}
