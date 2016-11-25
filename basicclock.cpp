#include "basicclock.h"
#include "ClockDigitsHelper.h"
#include <time.h>


//
// BasicClock
//
BasicClock::BasicClock()
    : mColor(0, 32, 32)
    , mX(0)
    , mY(2)
    , mWidth(14)
    , mHeight(29)
    , mThickness(3)
    , mSpace(1)
    , mDivider(3)
{
}

BasicClock::BasicClock(int x, int y, int w, int h, int t, int ds, int dv, const Color & c)
    : mColor(c)
    , mX(x)
    , mY(y)
    , mWidth(w)
    , mHeight(h)
    , mThickness(t)
    , mSpace(ds)
    , mDivider(dv)
{
}

void BasicClock::Init(const Json::Value & config)
{
    const Json::Value & position = config["position"];
    mX = position["x"].asInt();
    mY = position["y"].asInt();
    const Json::Value & color = config["color"];
    mColor.R() = (uint8_t)color["r"].asInt();
    mColor.G() = (uint8_t)color["g"].asInt();
    mColor.B() = (uint8_t)color["b"].asInt();

    const Json::Value & options = config["options"];
    mWidth = options["width"].asInt();
    mHeight = options["height"].asInt();
    mThickness = options["thickness"].asInt();
    mSpace = options["space"].asInt();
    mDivider = options["divider"].asInt();

    const Json::Value & shadow = config["shadow"];
    if (shadow.isObject()) {
        mShadowEnabled = true;
        const Json::Value & color = config["color"];
        mShadowColor.R() = (uint8_t)color["r"].asInt();
        mShadowColor.G() = (uint8_t)color["g"].asInt();
        mShadowColor.B() = (uint8_t)color["b"].asInt();

        const Json::Value & position = config["offset"];
        mShadowOffsetX = position["x"].asInt();
        mShadowOffsetY = position["y"].asInt();
    }
}

void BasicClock::Draw(Bitmap & bitmap)
{
    time_t t = time(NULL);
    tm ti;
#ifdef _MSC_VER
    localtime_s(&ti, &t);
#else
    ti = (*localtime(&t));
#endif
    DrawClock(bitmap, mX, mY, mWidth, mHeight, mThickness, mSpace, mDivider, (uint8_t)ti.tm_hour, (uint8_t)ti.tm_min, ti.tm_sec % 2 == 1);
}

void BasicClock::DrawClock(Bitmap & bitmap, int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div)
{
    ClockDigitsHelper helper(bitmap);
    if (mShadowEnabled) {
        helper.Draw2Dig(x + mShadowOffsetX , y + mShadowOffsetY, w, h, t, ds, d1, mShadowColor);
        helper.Draw2Dig(x + mShadowOffsetX + 2 * (w + ds) + dv + ds, y + mShadowOffsetY, w, h, t, ds, d2, mShadowColor);
        if (div) {
            helper.DrawDiv(x + mShadowOffsetX + 2 * w + ds, y + mShadowOffsetY, 2 * ds + dv, h, dv, mShadowColor);
        }
    }
    helper.Draw2Dig(x, y, w, h, t, ds, d1, mColor);
    helper.Draw2Dig(x + 2 * (w + ds) + dv + ds, y, w, h, t, ds, d2, mColor);
    if (div) {
        helper.DrawDiv(x + 2 * w + ds, y, 2 * ds + dv, h, dv, mColor);
    }
}
