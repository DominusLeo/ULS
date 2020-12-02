#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int lengt_sub;

    if (!str || !sub)
        return -2;
    lengt_sub = mx_strlen(sub) - 1;
    for (int i = 0; str[i]; i++)
        if(mx_strncmp(&str[i], sub, lengt_sub) == 0)
            return i;
    return -1;
}
