#include <unistd.h>
#include "syscall.h"
#include <stddef.h>
#include <sys/types.h>

int close(int fd) {
    return __syscall_ret(__syscall1(SYS_close, fd));
}