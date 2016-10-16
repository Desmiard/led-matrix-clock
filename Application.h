#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#include "led-matrix.h"
#include "bitmap.h"
#include "widget.h"
#include "preset.h"

//
// Application
//
class Application
{
private:
    rgb_matrix::Canvas * mCanvas;
    Bitmap               mFrontBuffer;

    std::vector<std::shared_ptr<Preset>> mPresetList;

    std::shared_ptr<Preset> mCurrentPreset;


    std::string GetConfig();
    std::shared_ptr<Preset> GetBestMatchingPreset();

    void Configurate();
    void DrawFrame();
public:
    Application();
    ~Application();

    bool Init(int argc, char *argv[]);
    void Run();

    int ExitCode();
};

#endif
