#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "led-matrix.h"
#include "color.h"

//
// Forward declarations
//
namespace rgb_matrix
{
    class Canvas;
}

//
// Application
//
class Application
{
private:
    rgb_matrix::Canvas * mCanvas;

    enum
    {
        WIDTH = 64,
        HEIGHT = 32,
    };

    Color mBackBuffer[HEIGHT][WIDTH];

    void DrawSeg(int x, int y, int w, int h, int t, uint8_t m);
    void DrawDig(int x, int y, int w, int h, int t, uint8_t v);

    void DrawVSeg(int x, int y, int w, int h);
    void DrawHSeg(int x, int y, int w, int h);

    void Draw2Dig(int x, int y, int w, int h, int t, int s, uint8_t v);

    void DrawClock(int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div);

    void DrawDiv(int x, int y, int w, int h, int t);

    void LineV(int x, int y, int h);
    void LineH(int x, int y, int w);
    void Rectangle(int x, int y, int w, int h);

    void Clear();
    void Blt();

    void DrawFrame();
public:
    Application();
    ~Application();

    bool Init(int argc, char *argv[]);
    void Run();

    int ExitCode();
};

#endif
