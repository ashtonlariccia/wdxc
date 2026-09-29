#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/types.h>

#define SIGHUP 1
#define SIGINT 2
#define SIGKILL 9
#define SIGUSR1 10
#define SIGUSR2 12
#define SIGTERM 15
#define SIGCHLD 17
#define SIGCONT 18
#define SIGSTOP 19
#define SIGPWR 30

typedef unsigned long sigset_t;
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int sig);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

#define SIG_BLOCK 0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2

int kill(pid_t pid, int sig);

#endif