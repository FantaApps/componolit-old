#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>

int getrlimit(int resource, struct rlimit *rlim)
{
    errno = 0;
    return 0;
}

pid_t
getpid(void)
{
    return 42;
};

int
pthread_condattr_getclock(const void *restrict attr, void *restrict clock_id)
{
    return EINVAL;
}

int sched_yield(void)
{
   return 0;
}
