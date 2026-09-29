#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

int main(void) {
    /* 0x0100: exited with status 1 */
    int s1 = 0x0100;
    if (!WIFEXITED(s1))       return 1;
    if (WEXITSTATUS(s1) != 1) return 2;
    if (WIFSIGNALED(s1))      return 3;
    if (WIFSTOPPED(s1))       return 4;
    if (WTERMSIG(s1) != 0)    return 5;

    /* 0x0009: killed by SIGKILL (9) */
    int s2 = 0x0009;
    if (WIFEXITED(s2))              return 6;
    if (!WIFSIGNALED(s2))           return 7;
    if (WTERMSIG(s2) != SIGKILL)    return 8;
    if (WIFSTOPPED(s2))             return 9;

    /* 0x137f: stopped by SIGSTOP (19) */
    int s3 = 0x137f;
    if (WIFEXITED(s3))             return 10;
    if (WIFSIGNALED(s3))           return 11;
    if (!WIFSTOPPED(s3))           return 12;
    if (WSTOPSIG(s3) != SIGSTOP)   return 13;

    msg("wmacros test passed\n");
    return 0;
}
