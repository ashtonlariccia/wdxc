#include <unistd.h>
#include <string.h>

int main(void) {
    const char *msg = "Hello from wdxc(v0.1)!\n";
    write(1, msg, strlen(msg));
    return 0;
}