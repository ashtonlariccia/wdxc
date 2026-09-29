#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

int main(void) {
    sigset_t set;
    if (sigemptyset(&set) != 0) return 1;
    if (sigaddset(&set, SIGUSR1) != 0) return 2;

    if (sigprocmask(SIG_BLOCK, &set, 0) != 0) return 3;

    int fd = signalfd(-1, &set, SFD_CLOEXEC);
    if (fd < 0) return 4;

    if (kill(getpid(), SIGUSR1) != 0) return 5;

    struct signalfd_siginfo info;
    memset(&info, 0, sizeof info);
    ssize_t r = read(fd, &info, sizeof info);
    if (r != 128) return 6;

    if (info.ssi_signo != (uint32_t)SIGUSR1) return 7;
    if (info.ssi_pid != (uint32_t)getpid()) return 8;

    if (close(fd) != 0) return 9;

    msg("signalfd test passed\n");
    return 0;
}
