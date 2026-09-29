#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H

#define MS_RDONLY 1
#define MS_NOSUID 2
#define MS_NODEV 4
#define MS_NOEXEC 8
#define MS_REMOUNT 32
#define MS_BIND 4096
#define MS_MOVE 8192
#define MS_REC 16384
#define MS_RELATIME 2097152

int mount(const char *source, const char *target, const char *fstype, unsigned long flags, const void *data);

#endif