#include "libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
    char *str3;

    if(s2 == NULL && s1 == NULL)
       return NULL;
    if(s1 == NULL)
        return mx_strdup(s2);
    else if(s2 == NULL)
        return mx_strdup(s1);
    else {
        str3 = mx_strnew(mx_strlen(s1) + mx_strlen(s2) - 1);
        str3 = mx_strcat(str3, s1);
        str3 = mx_strcat(str3, s2);
    }
    return str3;
}
