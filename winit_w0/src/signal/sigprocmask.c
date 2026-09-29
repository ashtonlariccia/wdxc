#include <signal.h>
#include "syscall.h"

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
    return __syscall_ret(__syscall4(SYS_rt_sigprocmask, how, (long)set, (long)oldset, 8));
}