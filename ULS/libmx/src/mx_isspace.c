#include "libmx.h"

bool mx_isspace(char c) {
    if (( c > 8 && c < 14) || c == 32) 
        return 1;
    return 0;
}
