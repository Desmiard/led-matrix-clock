#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#ifndef _MSC_VER
#include "led-matrix.h"
#endif
#include "bitmap.h"
#include "widget.h"
#include "preset.h"
#include "filemonitor.h"
#include "timer.h"

//
// Application
//
class Application
{
private:
#ifndef _MSC_VER
    rgb_matrix::Canvas * mCanvas;
#endif
    Bitmap               mFrontBuffer;

    std::vector<std::shared_ptr<Preset>> mPresetList;

    std::shared_ptr<Preset> mCurrentPreset;
    std::shared_ptr<Preset> mDefaultPreset;

    std::string GetConfig();
    std::shared_ptr<Preset> GetBestMatchingPreset();

    std::string mConfigFile;
    FileMonitor mFileMonitor;
    Timer       mTimer;

    void DoConfig();
    void Configurate();
    void Update(int msec);

    void UpdateConfig();
    void UpdatePreset();

    void DrawFrame();
    void Loop();
public:
    Application();
    ~Application();

    bool Init(int argc, char *argv[]);
    void Run();

    int ExitCode();
};

#endif
