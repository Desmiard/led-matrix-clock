#include "Application.h"

#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

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
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    return true;
}

void Application::DrawFrame()
{
    mCanvas->Clear();
    mCanvas->SetPixel(10, 10, 255, 255, 255);
}

void Application::Run()
{
    // It is always good to set up a signal handler to cleanly exit when we
    // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
    // for that.
    // Animation finished. Shut down the RGB matrix.
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
