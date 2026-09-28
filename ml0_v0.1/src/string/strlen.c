#include <string.h>
unsigned long strlen(const char *str) {
    unsigned long length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}