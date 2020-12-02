#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    char *hex = NULL;
    unsigned long temp;
    int lengt = 0;

    if(nbr == 0) {
        return mx_strdup("0");
    }
    for(temp = nbr; temp !=0; lengt++)
        temp /= 16;
    hex = mx_strnew(lengt);
    lengt--;
    for (; nbr != 0; nbr /= 16) {
        temp = nbr % 16;
        if(temp < 10)
            hex[lengt--] = temp + 48;
        else
            hex[lengt--] = temp + 87;
    }
    return hex;
}
