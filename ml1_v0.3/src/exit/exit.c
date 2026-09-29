#include <syscall_arch.h>
#include <bits/syscall.h>
#include <stdlib.h>

_Noreturn void exit(int status) {
    for (;;) {
        __syscall1(SYS_exit_group, status);
    }
}