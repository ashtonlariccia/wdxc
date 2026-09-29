#include <time.h>
#include "syscall.h"

int nanosleep(const struct timespec *req, struct timespec *rem) {
    return __syscall_ret(__syscall2(SYS_nanosleep, (long)req, (long)rem));
}