#include <sys/wait.h>
#include "syscall.h"

pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage) {
    return __syscall_ret(__syscall4(SYS_wait4, pid, (long)wstatus, options, (long)rusage));
}