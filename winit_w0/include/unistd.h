#ifndef _UNISTD_H
#define _UNISTD_H

#include <stddef.h>
#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t n);
ssize_t read(int fd, void *buf, size_t n);

int dup2(int oldfd, int newfd);

int open(const char *path, int flags, ...);
int close(int fd);

pid_t getpid(void);
uid_t getuid(void);
pid_t setsid(void);
pid_t fork(void);
int execve(const char *path, char *const argv[], char *const envp[]);

_Noreturn void _exit(int status);

void sync(void);
int sethostname(const char *name, size_t len);
unsigned sleep(unsigned seconds);

extern char **environ;

#endif