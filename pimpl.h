#ifndef PIMPL_H
#define PIMPL_H
#include <stdexcept>
#include <cstdint>
#include <vector>

class Pimpl
{
public:
    Pimpl() = default;
    virtual double setTimeStamp(unsigned num) = 0;

    virtual double getSTimeStamp(unsigned num) = 0;
    virtual int64_t getMSTimeStamp(unsigned num) = 0;

    virtual double getSDiff(unsigned first, unsigned second) = 0;
    virtual int64_t getMSDiff(unsigned first, unsigned second) = 0;

    virtual bool isLess(unsigned first, unsigned second, int64_t expected) = 0;
    virtual bool isLess(unsigned num, int64_t expected) = 0;

};

#endif // PIMPL_H
