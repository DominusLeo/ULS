#include "libmx.h"

void mx_printstr(const char *s) {
    if (s == NULL)
        write(1, "(NULL)\n", 7);
    write(1, s, mx_strlen(s));
}
