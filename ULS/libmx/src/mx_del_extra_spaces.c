#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    char *cleared = NULL;
    char *tmp = NULL;
    int j = 0;

    if (str == NULL)
        return NULL;
    tmp = mx_strnew(mx_strlen(str));
    for (int i = 0; str[i] != '\0'; i++) {
        if (mx_isspace(str[i]) == 0) {
            tmp[j] = str[i];
            j++;
        }
        if (mx_isspace(str[i]) == 0 && mx_isspace(str[i + 1]) == 1) {
            tmp[j] = ' ';
            j++;
        }
    }
    cleared = mx_strtrim(tmp);
    mx_strdel(&tmp);
    return cleared;
}

/*static char to_space(char c) {
    if(mx_isspace(c))
        c = ' ';
    return c;
}
static int size_char(char *temp) {
    int count = 0;

    for(int i = 0; temp[i]; i++)
        if(mx_isspace(temp[i]))
            for (; mx_isspace(temp[i + 1]); i++, count++);
    return count;
}

char *mx_del_extra_spaces(const char *str) {
    char *clear_name = NULL;
    int count;
    int j = 0;
    char *temp;

    temp = mx_strtrim(str);
    if(str == NULL)
        return NULL;
    count = size_char(temp);
    clear_name = mx_strnew(count);
    for(int i = 0; temp[i]; i++, j++) {
        if(mx_isspace(temp[i])) {
            for (; mx_isspace(temp[i + 1]); i++);
        }
        //temp[i] = to_space(temp[i]);
        clear_name[j] = temp[i];
    }
    mx_strdel(&temp);
    return clear_name;
}*/
