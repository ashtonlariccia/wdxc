#include <signal.h>
#include "syscall.h"

int kill(pid_t pid, int sig) {
    return __syscall_ret(__syscall2(SYS_kill, pid, sig));
}