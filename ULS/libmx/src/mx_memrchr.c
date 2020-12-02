#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    char *sym = (char *) s;

    if(!s)
        return NULL;
    for (size_t i = mx_strlen(sym); n > 0 ; i--, n--)
        if (sym[i] == c)
            return (void *) &sym[i];
    return NULL;
}
