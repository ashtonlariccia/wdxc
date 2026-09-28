#include <bits/syscall.h>
#include <syscall_arch.h>
#include <unistd.h>

long write(int fd, const void *buf, unsigned long n) {
    return __syscall3(SYS_write, fd, (long)buf, n);
}