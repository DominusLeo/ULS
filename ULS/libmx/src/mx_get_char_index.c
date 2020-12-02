#include "libmx.h"

int mx_get_char_index(const char *str, char c) {
    int index = -1;

    if (!str)
        return -2;
    for (int i = 0; str[i]; i++) {
        index++;
        if (str[i] == c)
            return index;
    }
    return -1;
}
