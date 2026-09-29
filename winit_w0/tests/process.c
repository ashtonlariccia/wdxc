#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

/* Re-exec mode: when invoked as "<self> <digit>", just exit with that
   digit as the status. This gives the execve() checks below a target that
   always exists, instead of depending on /bin/true and /bin/false being at
   some particular path (they aren't, in wdxc's own initramfs). */
static void run_as_reexec_helper(const char *code) {
    _exit(code[0] - '0');
}

int main(int argc, char **argv, char **envp) {
    if (argc == 2) {
        run_as_reexec_helper(argv[1]);
    }

    pid_t pid = getpid();
    if (pid <= 0) return 1;

    char *const exit1_argv[] = { argv[0], "1", 0 };
    char *const exit0_argv[] = { argv[0], "0", 0 };

    /* fork + execve(self "1") + waitpid: exit status 1 */
    pid_t c1 = fork();
    if (c1 < 0) return 2;
    if (c1 == 0) {
        execve(argv[0], exit1_argv, envp);
        _exit(126);
    }
    int st1;
    if (waitpid(c1, &st1, 0) != c1) return 3;
    if (!WIFEXITED(st1)) return 4;
    if (WEXITSTATUS(st1) != 1) return 5;

    /* fork + execve(self "0") + waitpid: exit status 0 */
    pid_t c2 = fork();
    if (c2 < 0) return 6;
    if (c2 == 0) {
        execve(argv[0], exit0_argv, envp);
        _exit(126);
    }
    int st2;
    if (waitpid(c2, &st2, 0) != c2) return 7;
    if (!WIFEXITED(st2)) return 8;
    if (WEXITSTATUS(st2) != 0) return 9;

    /* child calls _exit(42) directly */
    pid_t c3 = fork();
    if (c3 < 0) return 10;
    if (c3 == 0) {
        _exit(42);
    }
    int st3;
    if (waitpid(c3, &st3, 0) != c3) return 11;
    if (!WIFEXITED(st3)) return 12;
    if (WEXITSTATUS(st3) != 42) return 13;

    /* execve of a nonexistent path -> -1, ENOENT; child _exit(127); parent sees 127 */
    pid_t c4 = fork();
    if (c4 < 0) return 14;
    if (c4 == 0) {
        char *const bad_argv[] = { "/nonexistent/wdxc-xyz123", 0 };
        int rc = execve(bad_argv[0], bad_argv, envp);
        if (rc == -1 && errno == ENOENT) {
            _exit(127);
        }
        _exit(126);
    }
    int st4;
    if (waitpid(c4, &st4, 0) != c4) return 15;
    if (!WIFEXITED(st4)) return 16;
    if (WEXITSTATUS(st4) != 127) return 17;

    /* child kills itself with SIGKILL */
    pid_t c5 = fork();
    if (c5 < 0) return 18;
    if (c5 == 0) {
        kill(getpid(), SIGKILL);
        _exit(125); /* unreachable if kill worked */
    }
    int st5;
    if (waitpid(c5, &st5, 0) != c5) return 19;
    if (!WIFSIGNALED(st5)) return 20;
    if (WTERMSIG(st5) != SIGKILL) return 21;
    if (WIFEXITED(st5)) return 22;

    /* wait4(-1, &st, WNOHANG, 0) with a running child returns 0 */
    pid_t c6 = fork();
    if (c6 < 0) return 23;
    if (c6 == 0) {
        for (volatile long i = 0; i < 200000000L; i++) {}
        _exit(0);
    }
    int st6;
    pid_t wr = wait4(-1, &st6, WNOHANG, 0);
    if (wr != 0) return 24;
    if (waitpid(c6, &st6, 0) != c6) return 25; /* reap it so it isn't left a zombie */

    /* setsid in a forked child succeeds; a second setsid() in the same
       process (now a session/group leader) fails with EPERM. Doing both
       calls in one freshly forked child makes this deterministic
       regardless of whether the test binary itself happens to already be
       a process group leader when launched. */
    pid_t c7 = fork();
    if (c7 < 0) return 26;
    if (c7 == 0) {
        pid_t sid = setsid();
        if (sid <= 0) _exit(1);
        pid_t sid2 = setsid();
        if (sid2 != -1) _exit(2);
        if (errno != EPERM) _exit(3);
        _exit(0);
    }
    int st7;
    if (waitpid(c7, &st7, 0) != c7) return 27;
    if (!WIFEXITED(st7)) return 28;
    if (WEXITSTATUS(st7) != 0) return 29;

    /* kill(getpid(), 0) returns 0 */
    if (kill(getpid(), 0) != 0) return 31;

    msg("process test passed\n");
    return 0;
}
