#ifndef _UNISTD_H
#define _UNISTD_H

#include <stddef.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t n);
int close(int fd);
ssize_t read(int fd, void *buf, size_t n);
int dup2(int oldfd, int newfd);
int open(const char *path, int flags, ...);

#endif