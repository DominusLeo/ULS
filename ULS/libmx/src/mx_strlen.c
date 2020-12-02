#include "libmx.h"

int mx_strlen(const char *s) {
    int lengt = 0;

    if (!s)
        return 0;
    for (; s[lengt]; lengt++);
    return lengt;
}
