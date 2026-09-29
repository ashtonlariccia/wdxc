#include <unistd.h>
#include "syscall.h"

int execve(const char *path, char *const argv[], char *const envp[]) {
    return __syscall_ret(__syscall3(SYS_execve, (long)path, (long)argv, (long)envp));
}