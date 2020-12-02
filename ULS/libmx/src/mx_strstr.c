#include "libmx.h"

char *mx_strstr(const char *s1, const char *s2) {
    int lengt_s2 = mx_strlen(s2);

    if(!s2)
        return (char *) s1;
    for(; *s1; s1++)
        if(mx_strncmp(s1, s2, lengt_s2) == 0)
            return(char *) s1;
    return NULL;
}
