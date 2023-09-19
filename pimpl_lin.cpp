#include "pimpl_lin.h"
#include <math.h>

Pimpl_Lin::Pimpl_Lin(unsigned count) {
    for (int i = 0; i < count; ++i) {
        meters.push_back(0);
    }
    clock_gettime(CLOCK_REALTIME, &start);
}
double Pimpl_Lin::setTimeStamp(unsigned num) {
    clock_gettime(CLOCK_REALTIME, &end);
    meters[num - 1] = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
}

double Pimpl_Lin::getSTimeStamp(unsigned num) {
    return meters[num - 1];
}
int64_t Pimpl_Lin::getMSTimeStamp(unsigned num) {
    return static_cast<int64_t>(meters[num - 1] * 1000);
}

double Pimpl_Lin::getSDiff(unsigned first, unsigned second) {
    return abs(meters[first - 1] - meters[second - 1]);
}
int64_t Pimpl_Lin::getMSDiff(unsigned first, unsigned second) {
    return abs(static_cast<int64_t>(meters[first - 1] * 1000) - static_cast<int64_t>(meters[second - 1] * 1000));
}

bool Pimpl_Lin::isLess(unsigned first, unsigned second, int64_t expected) {
    if (getMSDiff(first, second) <= expected) {
        return true;
    }
    return false;
}
bool Pimpl_Lin::isLess(unsigned num, int64_t expected) {
    if (static_cast<int64_t>(meters[num - 1] * 1000) <= expected) {
        return true;
    }
    return false;
}
