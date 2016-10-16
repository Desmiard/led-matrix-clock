#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <stdint.h>
#include "led-matrix.h"
#include "bitmap.h"

//
// Application
//
class Application
{
private:
    rgb_matrix::Canvas * mCanvas;
    Bitmap mFrontBuffer;
    Color mColor;

    void DrawSeg(int x, int y, int w, int h, int t, uint8_t m);
    void DrawDig(int x, int y, int w, int h, int t, uint8_t v);

    void DrawVSeg(int x, int y, int w, int h);
    void DrawHSeg(int x, int y, int w, int h);

    void Draw2Dig(int x, int y, int w, int h, int t, int s, uint8_t v);

    void DrawClock(int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div);

    void DrawDiv(int x, int y, int w, int h, int t);


    void DrawFrame();
public:
    Application();
    ~Application();

    bool Init(int argc, char *argv[]);
    void Run();

    int ExitCode();
};

#endif
