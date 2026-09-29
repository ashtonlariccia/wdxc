#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    const char *path = "/tmp/wdxc_io_test.txt";
    const char *msg = "wdxc io test\n";
    size_t len = strlen(msg);

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return 1;

    ssize_t w = write(fd, msg, len);
    if (w != (ssize_t)len) return 2;

    if (close(fd) != 0) return 3;

    int rfd = open(path, O_RDONLY);
    if (rfd < 0) return 4;

    char buf[64];
    ssize_t r = read(rfd, buf, sizeof(buf));
    if (r != (ssize_t)len) return 5;
    if (memcmp(buf, msg, len) != 0) return 6;

    int dupfd = 10;
    if (dup2(rfd, dupfd) != dupfd) return 7;
    if (dup2(dupfd, dupfd) != dupfd) return 8;

    if (close(dupfd) != 0) return 9;
    if (close(rfd) != 0) return 10;
    if (close(rfd) == 0) return 11;

    if (dup2(9999, 9998) == 9998) return 12;

    const char *ok = "io test passed\n";
    write(1, ok, strlen(ok));
    return 0;
}
