#pragma once

#include "../libmx/inc/libmx.h"

//======== includes ========//
#include <fcntl.h>
#include <limits.h>
#include <malloc/malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/acl.h>

#include <uuid/uuid.h>

struct entry
{
char d_name[13];
};
