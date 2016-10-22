#include "timer.h"
#include <chrono>
#include <thread>

void Timer::Sleep(int msec)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}

void Timer::Init()
{
    mMark = std::chrono::system_clock::now();
}

int Timer::Elapsed()
{
    auto start = mMark;
    Init();
    return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(mMark - start).count());
}