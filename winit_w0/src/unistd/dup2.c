#include <unistd.h>
#include "syscall.h"
#include <stddef.h>
#include <sys/types.h>
#include <fcntl.h>

int dup2(int oldfd, int newfd) {
    if (oldfd == newfd) {
        if (__syscall_ret(__syscall2(SYS_fcntl, oldfd, F_GETFD)) == -1) {
            return -1;
        } else {
            return newfd;
        }
    } else {
        return __syscall_ret(__syscall3(SYS_dup3, oldfd, newfd, 0));
    }
}