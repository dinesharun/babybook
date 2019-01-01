//
// Created by Indumathi Dinesh on 31/12/18.
//

#include <time.h>
#include "misc.h"

uint32 currTimeMS() {
    struct timespec t;
    uint32 ms = 0u;

    clock_gettime(CLOCK_MONOTONIC, &t);
    ms = (uint32)((1000 * (uint32)t.tv_sec) + ((uint32)t.tv_nsec / 1e6));

    return ms;
}

uint32 currTimeDiff(uint32 t0) {
    return timeDiff(currTimeMS(), t0);
}

uint32 timeDiff(uint32 t1, uint32 t0) {
    if(t1 >= t0) {
        return t1 - t0;
    } else {
        return ((MAX_UINT32) + (t0 - t1));
    }
}