#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static void msg(const char *s) {
    write(1, s, strlen(s));
}

int main(void) {
    const char *path = "/tmp/wdxc_fd_test.txt";
    const char *data = "wdxc fd test\n";
    size_t len = strlen(data);

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return 1;

    if (write(fd, data, len) != (ssize_t)len) return 2;
    if (close(fd) != 0) return 3;

    int rfd = open(path, O_RDONLY);
    if (rfd < 0) return 4;

    char buf[64];
    ssize_t r = read(rfd, buf, sizeof(buf));
    if (r != (ssize_t)len) return 5;
    if (memcmp(buf, data, len) != 0) return 6;
    if (close(rfd) != 0) return 7;

    /* open() on a missing path */
    int mfd = open("/tmp/wdxc_fd_test_missing_xyz", O_RDONLY);
    if (mfd != -1) return 8;
    if (errno != ENOENT) return 9;

    /* dup2 a file onto fd 1: save real stdout on fd 3, redirect, write, restore */
    if (dup2(1, 3) != 3) return 10;

    int wfd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (wfd < 0) return 11;
    if (dup2(wfd, 1) != 1) return 12;

    const char *via1 = "via fd 1\n";
    if (write(1, via1, strlen(via1)) != (ssize_t)strlen(via1)) return 13;
    if (close(wfd) != 0) return 14;

    if (dup2(3, 1) != 1) return 15;
    if (close(3) != 0) return 16;

    int checkfd = open(path, O_RDONLY);
    if (checkfd < 0) return 17;
    char buf2[32];
    ssize_t r2 = read(checkfd, buf2, sizeof(buf2));
    if (r2 != (ssize_t)strlen(via1)) return 18;
    if (memcmp(buf2, via1, strlen(via1)) != 0) return 19;
    if (close(checkfd) != 0) return 20;

    /* dup2(99, 99): fd 99 should not be open */
    if (dup2(99, 99) != -1) return 21;
    if (errno != EBADF) return 22;

    /* dup2(fd, fd) on a valid fd returns fd */
    int vfd = open(path, O_RDONLY);
    if (vfd < 0) return 23;
    if (dup2(vfd, vfd) != vfd) return 24;
    if (close(vfd) != 0) return 25;

    msg("fd test passed\n");
    return 0;
}
