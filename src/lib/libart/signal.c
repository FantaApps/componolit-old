#include <signal.h>

int sigwait(const sigset_t *set, int *sig)
{
    printf("%s: not implemented", __func__);
    *sig = SIGQUIT;
    return 0;
}

