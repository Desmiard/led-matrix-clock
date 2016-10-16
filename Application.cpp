#include "Application.h"

#include "led-matrix.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <cstring>
#include <signal.h>
#include <time.h>
#include "basicclock.h"
#include "json/json.h"

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

    Configurate();

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);
    return true;
}

void Application::DrawFrame()
{
    mFrontBuffer.Clear();
    if (mCurrentPreset) {
        mCurrentPreset->Draw(mFrontBuffer);
    }
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

std::string Application::GetConfig()
{
    return "{\"presets\":[{\"name\":\"main\",\"pages\":[{\"name\":\"main\",\"widgets\":[{\"type\":\"basic_clock\",\"position\":{\"x\":0,\"y\":2},\"color\":{\"r\":240,\"g\":60,\"b\":180},\"options\":{\"width\":14,\"height\":31,\"thickness\":3,\"space\":2,\"divider\":3}}]}]}]}";
}

std::shared_ptr<Preset> Application::GetBestMatchingPreset()
{
    return mPresetList.front();
}

void Application::Configurate()
{
    mCurrentPreset.reset();
    mPresetList.clear();
    const Json::Value json(GetConfig());
    const Json::Value & presets(json["presets"]);
    for (Json::Value::ArrayIndex i = 0; i < presets.size(); i++) {
        const Json::Value & presetConfig(presets.get(i, Json::Value::null));
        mPresetList.push_back(std::make_shared<Preset>(presetConfig));
    }
    mCurrentPreset = GetBestMatchingPreset();
}

int Application::ExitCode()
{
    return 0;
}
