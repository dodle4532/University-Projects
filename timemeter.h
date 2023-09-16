#ifndef TIMEMETER_H
#define TIMEMETER_H
#include <cstdint>
#include <memory>
#include "pimpl.h"
#include "pimpl_lin.h"
#include "pimpl_win.h"

class Pimpl;

class TimeMeter
{
public:
    TimeMeter(unsigned count);

    double setTimeStamp(unsigned num);

    double getSTimeStamp(unsigned num);
    int64_t getMSTimeStamp(unsigned num);

    double getSDiff(unsigned first, unsigned second);
    int64_t getMSDiff(unsigned first, unsigned second);

    bool isLess(unsigned first, unsigned second, int64_t expected);
    bool isLess(unsigned num, int64_t expected);

private:
    Pimpl* impl;
//    std::unique_ptr<Pimpl> impl;
};

#endif // TIMEMETER_H
