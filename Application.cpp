#include "Application.h"

#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <cstring>
#include <signal.h>
#include <time.h>
#include "basicclock.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

namespace
{
    volatile bool interrupt_received = false;
    static void InterruptHandler(int signo)
    {
        interrupt_received = true;
    }
}

//
// Application
//
Application::Application()
: mCanvas(NULL)
{
}

Application::~Application()
{
}

bool Application::Init(int argc, char *argv[])
{
    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";
    defaults.rows = 32;
    defaults.chain_length = 2;
    defaults.parallel = 1;
    defaults.show_refresh_rate = true;
    mCanvas = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
    if (mCanvas == NULL) {
        return false;
    }
    mFrontBuffer.Init(mCanvas->width(), mCanvas->height());
    mBasicClock = std::make_shared<BasicClock>();
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    return true;
}

void Application::DrawFrame()
{
    mFrontBuffer.Clear();
    mBasicClock->Draw(mFrontBuffer);
    mFrontBuffer.Blt(mCanvas);
}

void Application::Run()
{
    while (!interrupt_received) {
        DrawFrame();
    }
    mCanvas->Clear();
    delete mCanvas;
}

int Application::ExitCode()
{
    return 0;
}
