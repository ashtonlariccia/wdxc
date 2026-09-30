#ifndef _ERRNO_H
#define _ERRNO_H

int *__errno_location(void);
#define errno (*__errno_location())

#define EPERM 1
#define ENOENT 2
#define EINTR 4
#define EIO 5
#define EBADF 9
#define EBUSY 16
#define ENODEV 19
#define EAGAIN 11
#define ENOMEM 12
#define EACCES 13
#define EFAULT 14
#define EEXIST 17
#define EINVAL 22
#define ENOSPC 28
#define EPIPE 32
#define ERANGE 34
#define ENOSYS 38

#endif