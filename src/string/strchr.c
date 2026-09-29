#include <string.h>
#include <stddef.h>

char *strchr(const char *s, int c) {
    char ch = (char)c;
    while (*s != '\0') {
        if (*s == ch) {
            return (char *)s;
        }
        s++;
    }
    if (ch == '\0') {
        return (char *)s;
    }
    return NULL;
}