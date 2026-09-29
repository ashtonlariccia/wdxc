#include <unistd.h>
#include "syscall.h"
#include <stddef.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t n) {
    return __syscall_ret(__syscall3(SYS_write, fd, (long)buf, n));
}