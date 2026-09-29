#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#include <sys/types.h>

struct rusage;

pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
pid_t waitpid(pid_t pid, int *status, int options);

#define WNOHANG 1
#define WUNTRACED 2

#define WTERMSIG(s) ((s) & 0x7f)
#define WEXITSTATUS(s) (((s) >> 8) & 0xff)
#define WIFEXITED(s) (WTERMSIG(s) == 0)
#define WIFSTOPPED(s) (((s) & 0xff) == 0x7f)
#define WSTOPSIG(s) WEXITSTATUS(s)
#define WIFSIGNALED(s) (WTERMSIG(s) != 0 && WTERMSIG(s) != 0x7f)

#endif