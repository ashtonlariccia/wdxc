#include <unistd.h>
#include "syscall.h"

pid_t setsid(void) {
    return __syscall_ret(__syscall0(SYS_setsid));
}