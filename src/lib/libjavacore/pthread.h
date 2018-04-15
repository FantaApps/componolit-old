#ifndef _LIBJAVACORE_PTHREAD_H_
#define _LIBJAVACORE_PTHREAD_H_

#include_next <pthread.h>
#include <errno.h>

inline int
pthread_setname_np(pthread_t thread, const char *name)
{
    errno = EINVAL;
    return -1;
}

#endif // _LIBJAVACORE_PTHREAD_H_
