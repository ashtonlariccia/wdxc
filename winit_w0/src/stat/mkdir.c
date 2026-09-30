#include <sys/stat.h>
#include "syscall.h"
#include <fcntl.h>

int mkdir(const char *path, mode_t mode) {
    return __syscall_ret(__syscall3(SYS_mkdirat, AT_FDCWD, (long)path, mode));
}