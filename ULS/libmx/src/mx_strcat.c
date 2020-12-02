#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
	int count = mx_strlen(s1);
	int i;

	for(i = 0; i < mx_strlen(s2); i++)
		s1[i+count] = s2[i];
	s1[i+count] = '\0';
	return s1;
}
