#include "libmx.h"

static void mx_shift(char **arr, int size) {
    char *temp = arr[0];
    int i;

    for (i = 0; i < size - 1; i++)
        arr[i] = arr[i + 1];
    arr[i] = temp;
}

void mx_str_rotate(char **arr, int size, int shift) {
    int i;

    if (shift < 0) {
        shift = -shift % size;
        for (i = 0; i < shift; i++)
            mx_shift(arr, size);
    }
    else if (shift >= 0) {
        shift = shift % size;
        shift = size - shift;
        for (i = 0; i < shift; i++)
            mx_shift(arr, size);
    }
}
