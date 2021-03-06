#include "libmx.h"

int mx_strcmp(const char *s1, const char *s2) {
    for (; *s1 && *s2 && (*s1 == *s2); s1++, s2++);
    return (unsigned char) *s1 - (unsigned char) *s2;
}
