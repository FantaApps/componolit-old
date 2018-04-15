#ifndef _SYS_PRCTL_
#define _SYS_PRCTL_

#include <errno.h>

#define PR_GET_NAME 0

inline int
prctl(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5)
{
    errno = EINVAL;
    return -1;
}

#endif // _SYS_PRCTL_
