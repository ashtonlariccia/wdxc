#ifndef _SYS_STAT_H
#define _SYS_STAT_H

#include <sys/types.h>

mode_t umask(mode_t mask);
int mkdir(const char *path, mode_t mode);

#endif