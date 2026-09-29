#include <unistd.h>
#include "syscall.h"

int sethostname(const char *name, size_t len) {
    return __syscall_ret(__syscall2(SYS_sethostname, (long)name, len));
}