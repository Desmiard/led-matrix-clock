#include "Application.h"

#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <math.h>
#include <stdio.h>
#include <cstring>
#include <signal.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "basicclock.h"
#include "json/json.h"

#ifndef _MSC_VER
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;
#endif

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
#ifndef _MSC_VER
: mCanvas(NULL)
#endif
{
}

Application::~Application()
{
}

bool Application::Init(int argc, char *argv[])
{
#ifndef _MSC_VER
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
#else
    mFrontBuffer.Init(64, 32);
#endif
    DoConfig();

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
#ifndef _MSC_VER
    mFrontBuffer.Blt(mCanvas);
#endif
}

void Application::Update()
{
    auto changed = mFileMonitor.Update();
    if (!changed.empty()) {
        Configurate();
    }
    if (mCurrentPreset) {
        mCurrentPreset->Update();
    }
}

void Application::Run()
{
    while (!interrupt_received) {
        Update();
        DrawFrame();
    }
#ifndef _MSC_VER
    mCanvas->Clear();
    delete mCanvas;
#endif
}

std::string ReadFileAsString(std::string fileName)
{
    std::ifstream file(fileName);
    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        size_t l = file.tellg();
        file.seekg(0, std::ios::beg);
        std::string result(l, ' ');
        file.read((char*)result.c_str(), result.length());
        file.close();
        return result;
    }
    return std::string();
}

std::string Application::GetConfig()
{
    return ReadFileAsString(mConfigFile);
}

std::shared_ptr<Preset> Application::GetBestMatchingPreset()
{
    if (!mPresetList.empty()) {
        return mPresetList.front();
    }
    return std::shared_ptr<Preset>();
}

void Application::DoConfig()
{
    mConfigFile = "/var/www/html/clock.json";
    mFileMonitor.AddWatch(mConfigFile);
    Configurate();
}


void Application::Configurate()
{
    mCurrentPreset.reset();
    mPresetList.clear();
    Json::Value json;
    Json::Reader reader;
    if (reader.parse(GetConfig(), json, true)) {
        const Json::Value & presets(json["presets"]);
        for (Json::Value::ArrayIndex i = 0; i < presets.size(); i++) {
            const Json::Value & presetConfig(presets.get(i, Json::Value::null));
            mPresetList.push_back(std::make_shared<Preset>(presetConfig));
        }
        mCurrentPreset = GetBestMatchingPreset();
    }
}

int Application::ExitCode()
{
    return 0;
}
