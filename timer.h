#ifndef __TIMER_H
#define __TIMER_H

#include <chrono>

//
// Timer
//
class Timer final
{
private:
    std::chrono::time_point<std::chrono::system_clock> mMark;
public:
    void Sleep(int msec);
    void Init();
    int Elapsed();
};


#endif//__TIMER_H
