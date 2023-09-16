#ifndef PIMPL_W_H
#define PIMPL_W_H
#include "pimpl.h"
#include <windows.h>

class Pimpl_Win : public Pimpl
{
public:
    Pimpl_Win(unsigned count);
    double setTimeStamp(unsigned num) override;

    double getSTimeStamp(unsigned num) override;
    int64_t getMSTimeStamp(unsigned num) override;

    double getSDiff(unsigned first, unsigned second) override;
    int64_t getMSDiff(unsigned first, unsigned second) override;

    bool isLess(unsigned first, unsigned second, int64_t expected) override;
    bool isLess(unsigned num, int64_t expected) override;

private:
    std::vector <double> meters;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    LARGE_INTEGER freq;
};

#endif // PIMPL_W_H