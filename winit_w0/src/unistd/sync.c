#include <unistd.h>
#include "syscall.h"

void sync(void) {
    __syscall0(SYS_sync);
}