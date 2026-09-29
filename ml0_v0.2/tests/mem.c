#include <string.h>

int main(void) {
    char buf[8] = "ABCDE";
    memmove(buf + 2, buf, 5);
    if (memcmp(buf, "ABABCDE", 7) != 0) return 3;
}