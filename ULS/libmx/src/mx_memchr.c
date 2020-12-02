#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    size_t i;
    char *sym = (char *) s;

    if (!s)
        return NULL;
    for (i = 0; sym[i] && i < n; i++)
        if (sym[i] == c)
           return (void *) &sym[i];
    return NULL;
}
