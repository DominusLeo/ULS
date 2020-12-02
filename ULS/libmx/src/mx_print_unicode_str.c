#include "libmx.h"

void mx_print_unicode_str(char *str) {
    for (int i = 0; str[i]; i++) {
        if (mx_isdigit(str[i])) {
            mx_print_unicode(mx_atoi(&str[i]));
            for (; mx_isdigit((str[i])); i++);
        }
        mx_printchar(str[i]);
    }
}
