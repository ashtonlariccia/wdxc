#include <sys/reboot.h>
#include "syscall.h"

int reboot(int cmd) {
    return __syscall_ret(__syscall4(SYS_reboot, 0xfee1dead, 672274793, cmd, 0));
}