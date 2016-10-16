#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <stdint.h>
#include <memory>
#include "led-matrix.h"
#include "bitmap.h"
#include "widget.h"

//
// Application
//
class Application
{
private:
    rgb_matrix::Canvas * mCanvas;
    Bitmap               mFrontBuffer;

    std::shared_ptr<Widget> mBasicClock;

    void DrawFrame();
public:
    Application();
    ~Application();

    bool Init(int argc, char *argv[]);
    void Run();

    int ExitCode();
};

#endif
