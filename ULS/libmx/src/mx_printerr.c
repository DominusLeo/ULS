#include "libmx.h"

void mx_printerr(const char *s) {
   if(s == NULL)
       return;
   write(2, s, mx_strlen(s));

}
