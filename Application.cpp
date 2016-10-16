#include "Application.h"

#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <cstring>
#include <signal.h>
#include <time.h>

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
    mColor = Color(0, 2, 2);
    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    return true;
}

void Application::DrawVSeg(int x, int y, int w, int h)
{
    int f = (w - 1) / 2;
    int m = w - 2 * f;
    for (int i = 0; i < f; ++i) {
        int k = f - i;
        mFrontBuffer.LineV(x + i, y + k, h - 2 * k, mColor);
    }
    for (int i = 0, o = f; i < m; ++i) {
        mFrontBuffer.LineV(x + i + o, y, h, mColor);
    }
    for (int i = 0, o = f + m; i < f; ++i) {
        int k = i + 1;
        mFrontBuffer.LineV(x + i + o, y + k, h - 2 * k, mColor);
    }
}

void Application::DrawHSeg(int x, int y, int w, int h)
{
    int f = (h - 1) / 2;
    int m = h - 2 * f;
    for (int i = 0; i < f; ++i) {
        int k = f - i;
        mFrontBuffer.LineH(x + k, y + i, w - 2 * k, mColor);
    }
    for (int i = 0, o = f; i < m; ++i) {
        mFrontBuffer.LineH(x, y + i + o, w, mColor);
    }
    for (int i = 0, o = f + m; i < f; ++i) {
        int k = i + 1;
        mFrontBuffer.LineH(x + k, y + i + o, w - 2 * k, mColor);
    }
}

inline bool TestBit(int bit, uint8_t mask) { return (mask & 1 << bit); }

void Application::DrawDig(int x, int y, int w, int h, int t, uint8_t v)
{
    const uint8_t tt[] = {
        0b01110111, // 0
        0b00100100, // 1
        0b01011110, // 2
        0b01101110, // 3
        0b00101101, // 4
        0b01101011, // 5
        0b01111011, // 6
        0b00100110, // 7
        0b01111111, // 8
        0b01101111, // 9
    };
    DrawSeg(x, y, w, h, t, tt[v]);
}

void Application::DrawSeg(int x, int y, int w, int h, int t, uint8_t m)
{
    int t2 = t + (h - 3 * t) % 2;

    int f  = (t  - 1) / 2;
    int f2 = (t2 - 1) / 2;

    int tf  = t - f;
    int thm  = t2 - 2 * f2;

    int hv = (h - (tf + tf + thm)) / 2;
    int yv1 = y + tf;
    int yv2 = yv1 + hv + thm;

    int xv1 = x;
    int xv2 = x + w - t;

    int xh  = x + tf;
    int wh  = w - 2 * tf;
    int yh1 = y;
    int yh2 = y + (h - t2) / 2;
    int yh3 = y + h - t;

    if (TestBit(0, m))DrawVSeg(xv1, yv1,  t, hv);
    if (TestBit(2, m))DrawVSeg(xv2, yv1,  t, hv);
    if (TestBit(4, m))DrawVSeg(xv1, yv2,  t, hv);
    if (TestBit(5, m))DrawVSeg(xv2, yv2,  t, hv);
    if (TestBit(1, m))DrawHSeg(xh, yh1, wh, t);
    if (TestBit(3, m))DrawHSeg(xh, yh2, wh, t2);
    if (TestBit(6, m))DrawHSeg(xh, yh3, wh, t);
}

void Application::Draw2Dig(int x, int y, int w, int h, int t, int s, uint8_t v)
{
    DrawDig(x, y, w , h, t, (v / 10) % 10);
    DrawDig(x + s + w, y, w , h, t, (v % 10));
}

void Application::DrawDiv(int x, int y, int w, int h, int t)
{
    int t2 = t + (w - t) % 2;
    int px = x + (w - t2) / 2;

    int q = t2 + h % 2;

    int y0 = y + h / 2;
    int y1 = y0 - t2 - t2;
    int y2 = y0 + q;

    mFrontBuffer.Rectangle(px, y1, t2, t2, mColor);
    mFrontBuffer.Rectangle(px, y2, t2, t2, mColor);
}

void Application::DrawClock(int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div)
{
    Draw2Dig(x, y, w, h, t, ds, d1);
    Draw2Dig(x + 2 * (w + ds) + dv + ds, y, w, h, t, ds, d2);
    if (div) {
        DrawDiv(x + 2 * w + ds, y, 2 * ds + dv, h, dv);
    }
}

void Application::DrawFrame()
{
    mFrontBuffer.Clear();

    time_t t = time(NULL);

    tm * ti = localtime(&t);

    DrawClock(0, 2, 14, 29, 3, 1, 3, (uint8_t)ti->tm_hour, (uint8_t)ti->tm_min, ti->tm_sec % 2);
    //DrawClock(0, 2, 8, 15, 1, 1, 1, (uint8_t)ti->tm_hour, (uint8_t)ti->tm_min, ti->tm_sec % 2);
    //DrawClock(0, 2, 14, 29, 3, 1, 3, (uint8_t)ti->tm_min, (uint8_t)ti->tm_sec, ti->tm_sec % 2);
    //DrawClock(0, 2, 14, 29, 3, 1, 3, 88, 88, true);
    mFrontBuffer.Blt(mCanvas);
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
