#include <signal.h>
#include <unistd.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

int main(void) {
    sigset_t block, query;

    if (sigemptyset(&block) != 0) return 1;
    if (sigaddset(&block, SIGUSR1) != 0) return 2;

    /* block SIGUSR1 */
    if (sigprocmask(SIG_BLOCK, &block, 0) != 0) return 3;

    /* query with set = NULL, oldset non-NULL */
    if (sigprocmask(SIG_BLOCK, 0, &query) != 0) return 4;
    if (!(query & (1UL << (SIGUSR1 - 1)))) return 5;

    /* SIG_UNBLOCK removes it */
    if (sigprocmask(SIG_UNBLOCK, &block, 0) != 0) return 6;
    if (sigprocmask(SIG_BLOCK, 0, &query) != 0) return 7;
    if (query & (1UL << (SIGUSR1 - 1))) return 8;

    /* SIG_SETMASK with an empty set clears everything */
    if (sigprocmask(SIG_BLOCK, &block, 0) != 0) return 9; /* re-block so there is something to clear */
    sigset_t empty;
    if (sigemptyset(&empty) != 0) return 10;
    if (sigprocmask(SIG_SETMASK, &empty, 0) != 0) return 11;
    if (sigprocmask(SIG_BLOCK, 0, &query) != 0) return 12;
    if (query != 0) return 13;

    msg("sigprocmask test passed\n");
    return 0;
}
