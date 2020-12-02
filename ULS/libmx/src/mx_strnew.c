#include "libmx.h"

char *mx_strnew(const int size) {
    char *string = NULL;

    if (size < 0)
        return NULL;
    string = (char *)malloc(size + 1);
    for(int i = 0; i < size; i++)
        string[i] = '\0';
    string[size] = '\0';
    return string;
}
