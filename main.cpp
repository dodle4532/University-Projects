#include <iostream>
#include "timemeter.h"
#include <unistd.h>

using namespace std;

int main()
{
    TimeMeter m(2);
    int mas[10000];
    sleep(3);
    m.setTimeStamp(1);
    std::cout << "Time spent: " << m.getMSTimeStamp(1) << " ms" << std::endl;
    std::cout << "Time spent: " << m.getSTimeStamp(1) << " s" << std::endl;
    sleep(2);
    for (int i = 0; i < 10000; ++i) {
        mas[i] = i*i*i;
    }
    m.setTimeStamp(2);
    std::cout << "Time spent: " << m.getMSTimeStamp(2) << " ms" << std::endl;
    std::cout << "Time spent: " << m.getSTimeStamp(2) << " s" << std::endl;

    std::cout << "Diff - " << m.getMSDiff(1, 2) << " ms";
}
