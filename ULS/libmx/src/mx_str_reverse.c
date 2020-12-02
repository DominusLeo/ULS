#include "libmx.h"

void mx_str_reverse(char *s) {
	int lengt;
	int j;

	if (!s)
        return;
	lengt = mx_strlen(s);
    j = lengt - 1;
	for (int i = 0; i < j; i++, j--)
		mx_swap_char(&s[j], &s[i]);
}
