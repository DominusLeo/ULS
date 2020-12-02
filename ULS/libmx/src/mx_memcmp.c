#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
        size_t i;

    for (i = 0; ((unsigned char *) s1)[i] && ((unsigned char *) s2)[i] &&
        (((unsigned char *) s1)[i] == ((unsigned char *) s2)[i]) && i < n; i++);
    return i < n ? ((unsigned char *) s1)[i] - ((unsigned char *) s2)[i] : 0;
}
