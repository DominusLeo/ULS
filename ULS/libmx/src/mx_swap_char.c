#include "libmx.h"

void mx_swap_char(char *s1, char *s2) {
	char str;

	if (!s1 || !s2)
        return;
	str = *s1;
	*s1 = *s2;	
	*s2 = str; 	
}
