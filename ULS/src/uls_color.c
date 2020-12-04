#include "uls.h"

void		uls_color(int c)
{
	c %= 7;
	if (c == 0)
		mx_printstr(LS_RED);
	else if (c == 1)
		mx_printstr(LS_YELLOW);
	else if (c == 2)
		mx_printstr(LS_GREEN);
	else if (c == 3)
		mx_printstr(LS_CYAN);
	else if (c == 4)
		mx_printstr(LS_BLUE);
	else if (c == 5)
		mx_printstr(LS_MAGENTA);
	else if (c == 6)
		mx_printstr(LS_NORMAL);
}
