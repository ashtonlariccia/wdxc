#include <unistd.h>
#include "syscall.h"

pid_t getpid(void) {
    return __syscall0(SYS_getpid);
}