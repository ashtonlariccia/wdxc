#include <string.h>


int strncmp(const char *a, const char *b, size_t n) {
    while (n > 0) {
        unsigned char u1 = (unsigned char)*a++;
        unsigned char u2 = (unsigned char)*b++;
        if (u1 != u2) {
            return u1 - u2;
        }
        if (u1 == '\0') {
            return 0;
        }
        n--;
    }
    return 0;
}