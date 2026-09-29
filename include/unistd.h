#ifndef _UNISTD_H
#define _UNISTD_H

#include <stddef.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t n);

#endif