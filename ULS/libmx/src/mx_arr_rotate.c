#include "libmx.h"

static void mx_shift(int *arr, int size) {
    int temp = arr[0];
    int i;

    for (i = 0; i < size - 1; i++)
        arr[i] = arr[i + 1];
    arr[i] = temp;
}


void mx_arr_rotate(int *arr, int size, int shift) {
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

//int main(void) {
//    int arr[] = {1, 2, 3, 4, 5};
//    int size = 5;
//    int shift = -11;
//
//    mx_arr_rotate(arr, size, shift);
//    for (int i = 0; i < size; i++) {
//        printf("%d ", arr[i]);
//    }
//}
