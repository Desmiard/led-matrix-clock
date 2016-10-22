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

void Application::UpdateConfig()
{
    auto changed = mFileMonitor.Update();
    if (!changed.empty()) {
        Configurate();
    }
}

void Application::UpdatePreset()
{
    auto preset = GetBestMatchingPreset();
    if (preset != mCurrentPreset) {
        if (mCurrentPreset) {
            mCurrentPreset->Deactivate();
        }
        mCurrentPreset = preset;
        if (mCurrentPreset) {
            mCurrentPreset->Activate();
        }
    }
}

void Application::Update(int msec)
{
    UpdateConfig();
    UpdatePreset();
    if (mCurrentPreset) {
        mCurrentPreset->Update(msec);
    }
}

void Application::Loop()
{
    while (!interrupt_received) {
        Update(mTimer.Elapsed());
        DrawFrame();
        mTimer.Sleep(15);
    }
}

void Application::Run()
{
    mTimer.Init();
    Loop();
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
        std::streamoff l = file.tellg();
        file.seekg(0, std::ios::beg);
        std::string result(static_cast<size_t>(l), ' ');
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
    for (auto it : mPresetList) {
        if (it->Test()) {
            return it;
        }
    }
    if (mDefaultPreset) {
        return mDefaultPreset;
    }
    if (!mPresetList.empty()) {
        return mPresetList.front();
    }
    return std::shared_ptr<Preset>();
}

void Application::DoConfig()
{
#ifndef _MSC_VER
    mConfigFile = "/var/www/html/clock.json";
#else 
    mConfigFile = "clock.json";
#endif
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
        std::string defaultPreset = json["default_preset"].asString();
        const Json::Value & presets(json["presets"]);
        for (Json::Value::ArrayIndex i = 0; i < presets.size(); i++) {
            const Json::Value & presetConfig(presets.get(i, Json::Value::null));
            auto preset = std::make_shared<Preset>(presetConfig);
            mPresetList.push_back(preset);
            if (preset->Name() == defaultPreset) {
                mDefaultPreset = preset;
            }
        }
    }
}

int Application::ExitCode()
{
    return 0;
}
