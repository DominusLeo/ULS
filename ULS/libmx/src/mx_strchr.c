#include "libmx.h"

char *mx_strchr(const char *s, int c) {
    int i = 0;

    for (; s[i] && s[i] != c; i++);
    if (c == s[i]) {
        return ((char *) s + i);
    }
   	return NULL;
    // return (c == s[i]) ? ((char*)s + i) : (NULL);
}
