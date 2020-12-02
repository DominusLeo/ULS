#include "libmx.h"

char *mx_file_to_str(const char *filename) {
    int content;
    char *dst_str;
    int count = 0;
    char buf;

    content = open(filename, O_RDONLY);
    if (content > 0) {
        for (; read(content, &buf, 1); count++);
        close(content);
        if (count > 0) {
            dst_str = mx_strnew(count);
            content = open(filename, O_RDONLY);
            for (int i = 0; read(content, &buf, 1); i++)
                dst_str[i] = buf;
            close(content);
            return dst_str;
        }
    }
    return NULL;
}
