#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

int main(void) {
    ssize_t r = write(99, "x", 1);
    if (r == -1 && errno == EBADF) {
        const char *errmsg = "r == -1 && errno == EBADF\n";
        write(1, errmsg, strlen(errmsg));
        return 0;
    } else {
        return 1;
    }
}