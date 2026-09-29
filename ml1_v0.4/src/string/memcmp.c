#include <string.h>

int memcmp(const void *a, const void *b, size_t n) {
    const unsigned char *c = a;
    const unsigned char *d = b;
    for (unsigned long i = 0; i < n; i++) {
        if (c[i] != d[i]) {
            return c[i] - d[i];
        }
    }
    return 0;
}