#include "uls.h"

void mx_putchar_fd(char c, int fd) {
	write(fd, &c, 1);
}
