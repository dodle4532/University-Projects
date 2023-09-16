#include "timemeter.h"
TimeMeter::TimeMeter(unsigned count) {
#ifdef WIN32
    impl = new Pimpl_Win(count);
#else
    impl = new Pimpl_Lin(count);
#endif
}

double TimeMeter::setTimeStamp(unsigned num) {
    return impl->setTimeStamp(num);
}

double TimeMeter::getSTimeStamp(unsigned num) {
    return impl->getSTimeStamp(num);
}

int64_t TimeMeter::getMSTimeStamp(unsigned num) {
    return impl->getMSTimeStamp(num);
}


double TimeMeter::getSDiff(unsigned first, unsigned second) {
    return impl->getSDiff(first, second);
}

int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) {
    return impl->getMSDiff(first, second);
}


bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) {
    return impl->isLess(first, second, expected);
}

bool TimeMeter::isLess(unsigned num, int64_t expected) {
    return impl->isLess(num, expected);
}
