#include <string.h>
#include <stddef.h>

char *strrchr(const char *s, int c) {
    const char *last = NULL;
    char target = (char)c;

    while (*s != '\0') {
        if (*s == target) {
            last = s;
        }
        s++;
    }

    if (*s == target) {
        last = s;
    }

    return (char *)last;
}