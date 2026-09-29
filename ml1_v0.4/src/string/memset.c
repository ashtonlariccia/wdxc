#include <string.h>

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    for (unsigned long i = 0; i < n; i++) {
        p[i] = (unsigned char)c;
    }
    return s;
}