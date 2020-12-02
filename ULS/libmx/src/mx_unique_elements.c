#include "libmx.h"

char **mx_unique_elements(char **src, int count) {
    char **dst = (char **)malloc(sizeof(char *) * count);
    int j;
    bool flag = true;

    for (int i = 0; i < count; i++)
        dst[i] = NULL;
    for (int i = 0; src[i] != NULL; i++) {
        flag = true;
        for (j = 0; dst[j] != NULL && j < count; j++)
            if (mx_strcmp(src[i], dst[j]) == 0)
                flag = false;
        if (flag)
            dst[j] = mx_strdup((src[i]));
    }
    return dst;
}
