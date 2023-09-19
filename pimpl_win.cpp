#include "pimpl_win.h"
#include <math.h>

Pimpl_Win::Pimpl_Win(unsigned count) {
    for (int i = 0; i < count; ++i) {
        meters.push_back(0);
    }
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
}
double Pimpl_Win::setTimeStamp(unsigned num) {
    QueryPerformanceCounter(&end);
    meters[num - 1] = (static_cast<double>(end.QuadPart - start.QuadPart) / freq.QuadPart);
}

double Pimpl_Win::getSTimeStamp(unsigned num) {
    if (meters[num - 1] == 0) {
        throw std::out_of_range("This meter is NULL");
    }
    return meters[num - 1];
}
int64_t Pimpl_Win::getMSTimeStamp(unsigned num) {
    if (meters[num - 1] == 0) {
        throw std::out_of_range("This meter is NULL");
    }
    return static_cast<int64_t>(meters[num - 1] * 1000);
}

double Pimpl_Win::getSDiff(unsigned first, unsigned second) {
    if (meters[first - 1] == 0) {
        throw std::out_of_range("This meter is NULL");
    }

    if (meters[second - 1] == 0) {
        throw std::out_of_range("This meter is NULL");
    }
    return abs(meters[first - 1] - meters[second - 1]);
}
int64_t Pimpl_Win::getMSDiff(unsigned first, unsigned second) {
    if (meters[first - 1] == 0) {
        throw std::out_of_range("This meter is NULL");
    }
    
    if (meters[second - 1] == 0) {
        throw std::out_of_range("This meter is NULL");
    }
    return abs(static_cast<int64_t>(meters[first - 1] * 1000) - static_cast<int64_t>(meters[second - 1] * 1000));
}

bool Pimpl_Win::isLess(unsigned first, unsigned second, int64_t expected) {
    if (getMSDiff(first, second) <= expected) {
        return true;
    }
    return false;
}
bool Pimpl_Win::isLess(unsigned num, int64_t expected) {
    if (meters[num - 1] == 0) {
        throw std::out_of_range("This meter is NULL");
    }
    
    if (static_cast<int64_t>(meters[num - 1] * 1000) <= expected) {
        return true;
    }
    return false;
}
