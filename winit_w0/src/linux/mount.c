#include <sys/mount.h>
#include "syscall.h"

int mount(const char *source, const char *target, const char *fstype, unsigned long flags, const void *data) {
    return __syscall_ret(__syscall5(SYS_mount, (long)source, (long)target, (long)fstype, flags, (long)data));
}