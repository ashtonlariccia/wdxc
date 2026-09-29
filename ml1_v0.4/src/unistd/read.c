#include <unistd.h>
#include "syscall.h"
#include <stddef.h>
#include <sys/types.h>

ssize_t read(int fd, void *buf, size_t n) {
    return __syscall_ret(__syscall3(SYS_read, fd, (long)buf, n));
}