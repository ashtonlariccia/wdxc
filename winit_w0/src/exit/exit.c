#include <unistd.h>
#include <stdlib.h>

_Noreturn void exit(int status) {
     _exit(status);
}