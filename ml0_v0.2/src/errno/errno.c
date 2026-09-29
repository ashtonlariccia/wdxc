#include "syscall.h"
#include <errno.h>

static int errno_value;
int *__errno_location(void) {
    return &errno_value;
}

long __syscall_ret(unsigned long r) {
    if (r > -4096UL) {
        errno = -r;
        return -1;
    } else {
        return r;
    }
}