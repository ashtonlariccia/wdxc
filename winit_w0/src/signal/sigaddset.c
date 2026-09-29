#include <signal.h>
#include <errno.h>

int sigaddset(sigset_t *set, int sig) {
    if (sig < 1 || sig > 64) {
        errno = EINVAL;
        return -1;
    }
    *set |= (1UL << (sig - 1));
    return 0;
}