#include <unistd.h>
#include "syscall.h"

pid_t fork(void) {
    return __syscall_ret(__syscall0(SYS_fork));
}