#include <unistd.h>
#include <time.h>

unsigned sleep(unsigned seconds) {
    struct timespec ts = {seconds, 0};
    int r = nanosleep(&ts, &ts);
    if (r != 0) {
        return ts.tv_sec;
    } else {
        return 0;
    }
}