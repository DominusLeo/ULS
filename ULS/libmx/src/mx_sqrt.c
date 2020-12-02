#include "libmx.h"

int mx_sqrt(int x) {
	int rslt = x;
	int div = x;

	if (x <= 0)
	    return 0;
	while(1) {
	    div = (x / div + div) / 2;
	    if(rslt > div)
	        rslt = div;
	    else if(rslt * rslt != x)
	        return 0;
	    else
	        return rslt;
	}
}
