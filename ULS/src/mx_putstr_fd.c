#include "uls.h"

void mx_putstr_fd(char const *s, int fd) {
	size_t i;

	if (s) {
		i = 0;
		while (s[i])
		{
			mx_putchar_fd(s[i], fd);
			i++;
		}
	}
}
