#include <sys/reboot.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

int main(void) {
    /* Safety: never call reboot() as real root. */
    if (getuid() == 0) {
        msg("running as uid 0; skipping reboot() call\n");
        return 0;
    }

    int r = reboot(RB_POWER_OFF);
    if (r != -1) return 1;
    if (errno != EPERM) return 2;

    msg("reboot test passed\n");
    return 0;
}
