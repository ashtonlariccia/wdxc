#include <sys/signalfd.h>
#include "syscall.h"

int signalfd(int fd, const sigset_t *mask, int flags) {
    return __syscall_ret(__syscall4(SYS_signalfd4, fd, (long)mask, 8, flags));
}