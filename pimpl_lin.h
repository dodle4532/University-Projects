#ifndef PIMPL_L_H
#define PIMPL_L_H
#include "pimpl.h"
#include <time.h>
#include <ctime>
struct timespec;


class Pimpl_Lin : public Pimpl
{
public:
    Pimpl_Lin(unsigned count);
    double setTimeStamp(unsigned num) override;

    double getSTimeStamp(unsigned num) override;
    int64_t getMSTimeStamp(unsigned num) override;

    double getSDiff(unsigned first, unsigned second) override;
    int64_t getMSDiff(unsigned first, unsigned second) override;

    bool isLess(unsigned first, unsigned second, int64_t expected) override;
    bool isLess(unsigned num, int64_t expected) override;

private:
    std::vector <double> meters;
    timespec start;
    timespec end;
};

#endif // PIMPL_L_H