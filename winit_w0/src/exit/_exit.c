#include <unistd.h>
#include <syscall_arch.h>
#include <bits/syscall.h>

_Noreturn void _exit(int status) {
    for (;;) {
        __syscall1(SYS_exit_group, status);
    }
}