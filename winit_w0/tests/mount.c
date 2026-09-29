#include <sys/mount.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

/* Run only under `unshare -rmu`: getuid() == 0 there (mapped fake root in a
   private user namespace), with private mount and UTS namespaces so none of
   this touches the host. */
static int run_inside_namespace(void) {
    if (mount("tmpfs", "/tmp", "tmpfs", MS_NOSUID | MS_NODEV, "mode=0755") != 0) return 1;

    int fd = open("/tmp/wdxc_mount_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return 2;
    const char *data = "mounted\n";
    if (write(fd, data, strlen(data)) != (ssize_t)strlen(data)) return 3;
    if (close(fd) != 0) return 3;

    int rfd = open("/tmp/wdxc_mount_test.txt", O_RDONLY);
    if (rfd < 0) return 4;
    char buf[32];
    ssize_t r = read(rfd, buf, sizeof(buf));
    if (r != (ssize_t)strlen(data) || memcmp(buf, data, strlen(data)) != 0) return 4;
    if (close(rfd) != 0) return 4;

    /* mount with a nonexistent fstype */
    if (mount("none", "/tmp", "wdxcnonexistentfs12345", 0, 0) != -1) return 5;
    if (errno != ENODEV) return 6;

    /* sethostname inside the UTS namespace */
    if (sethostname("midir-test", 10) != 0) return 7;

    int hfd = open("/proc/sys/kernel/hostname", O_RDONLY);
    if (hfd < 0) return 8;
    char hbuf[32];
    memset(hbuf, 0, sizeof hbuf);
    ssize_t hr = read(hfd, hbuf, sizeof(hbuf) - 1);
    close(hfd);
    if (hr < 10 || memcmp(hbuf, "midir-test", 10) != 0) return 9;

    /* a 65-byte name is rejected */
    char toolong[65];
    memset(toolong, 'x', sizeof toolong);
    if (sethostname(toolong, sizeof toolong) != -1) return 10;
    if (errno != EINVAL) return 11;

    msg("mount/uts (inside namespace) test passed\n");
    return 0;
}

/* Safe to run directly, with no namespace: an ordinary user must not be
   able to change the host's hostname. */
static int run_outside_namespace(void) {
    if (sethostname("midir-test", 10) != -1) return 12;
    if (errno != EPERM) return 13;

    msg("sethostname (outside namespace) test passed\n");
    return 0;
}

int main(void) {
    if (getuid() == 0) {
        return run_inside_namespace();
    } else {
        return run_outside_namespace();
    }
}
