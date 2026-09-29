#include <unistd.h>
#include "syscall.h"
#include <stddef.h>
#include <sys/types.h>
#include <stdarg.h>
#include <fcntl.h>

int open(const char *path, int flags, ...) {
    mode_t mode = 0;
    if (flags & O_CREAT) {
        va_list ap;
        va_start(ap, flags);
        mode = va_arg(ap, int);
        va_end(ap);
    }
    return __syscall_ret(__syscall4(SYS_openat, AT_FDCWD, (long)path, flags, mode));
}