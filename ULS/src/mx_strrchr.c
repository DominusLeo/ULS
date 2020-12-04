#include "uls.h"

char	*mx_strrchr(const char *s, int c)
{
	int		len;

	len = (int)mx_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (&(((char *)s)[len]));
		len--;
	}
	return (NULL);
}
