#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

int main(void) {
    sigset_t s;

    if (sigemptyset(&s) != 0) return 1;
    if (s != 0) return 2;

    if (sigfillset(&s) != 0) return 3;
    if (s != ~0UL) return 4;

    if (sigemptyset(&s) != 0) return 5;
    if (sigaddset(&s, SIGHUP) != 0) return 6;
    if (s != 1) return 7;

    if (sigemptyset(&s) != 0) return 8;
    if (sigaddset(&s, SIGCHLD) != 0) return 9;
    if (s != 0x10000UL) return 10;

    if (sigemptyset(&s) != 0) return 11;
    if (sigaddset(&s, 64) != 0) return 12;
    if (s != (1UL << 63)) return 13;

    if (sigaddset(&s, 0) != -1) return 14;
    if (errno != EINVAL) return 15;

    if (sigaddset(&s, 65) != -1) return 16;
    if (errno != EINVAL) return 17;

    msg("sigset test passed\n");
    return 0;
}
