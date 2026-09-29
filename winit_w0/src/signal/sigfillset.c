#include <signal.h>

int sigfillset(sigset_t *set) {
    *set = ~0UL;
    return 0;
}