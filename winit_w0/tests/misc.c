#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

int main(void) {
    /* umask(022) returns the previous mask (unspecified here); a second
       umask(022) then returns 022, since that's what the first call set */
    umask(022);
    if (umask(022) != 022) return 1;
    umask(022); /* leave it back at 022 */

    sync();

    struct timespec req = {0, 100000000L}; /* 0.1s */
    if (nanosleep(&req, 0) != 0) return 2;

    struct timespec bad = {0, 1000000000L};
    if (nanosleep(&bad, 0) != -1) return 3;
    if (errno != EINVAL) return 4;

    /* the interrupted-sleep (EINTR) path can't be tested yet: wdxc has no
       sigaction, so there's no way to deliver a signal with a handler that
       returns instead of terminating the process. Left untested. */

    if (sleep(1) != 0) return 5;

    msg("misc test passed\n");
    return 0;
}
