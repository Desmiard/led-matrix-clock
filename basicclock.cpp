#include "basicclock.h"
#include "ClockDigitsHelper.h"
#include <time.h>


//
// BasicClock
//
BasicClock::BasicClock()
: mColor(0, 32, 32)
, mPosition(0, 2)
, mSize(14, 29)
, mThickness(3)
, mSpace(1)
, mDivider(3)
{
}

void BasicClock::Init(const Json::Value & config)
{
    mPosition = Vector2::FromJson(config["position"]);
    mColor = Color::FromJson(config["color"]);
    mSize = Vector2::FromJson(config["options"]);

    const Json::Value & options = config["options"];
    mThickness = options["thickness"].asInt();
    mSpace = options["space"].asInt();
    mDivider = options["divider"].asInt();

    const Json::Value & shadow = config["shadow"];
    if (shadow.isObject()) {
        mShadowEnabled = true;
        mShadowColor = Color::FromJson(shadow["color"]);
        mShadowOffset = Vector2::FromJson(shadow["offset"]);
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
    DrawClock(bitmap, mPosition.X(), mPosition.Y(), mSize.X(), mSize.Y(), mThickness, mSpace, mDivider, (uint8_t)ti.tm_hour, (uint8_t)ti.tm_min, ti.tm_sec % 2 == 1);
}

void BasicClock::DrawClock(Bitmap & bitmap, int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div)
{
    ClockDigitsHelper helper(bitmap);
    if (mShadowEnabled) {
        helper.Draw2Dig(x + mShadowOffset.X() , y + mShadowOffset.Y(), w, h, t, ds, d1, mShadowColor);
        helper.Draw2Dig(x + mShadowOffset.X() + 2 * (w + ds) + dv + ds, y + mShadowOffset.Y(), w, h, t, ds, d2, mShadowColor);
        if (div) {
            helper.DrawDiv(x + mShadowOffset.X() + 2 * w + ds, y + mShadowOffset.Y(), 2 * ds + dv, h, dv, mShadowColor);
        }
    }
    helper.Draw2Dig(x, y, w, h, t, ds, d1, mColor);
    helper.Draw2Dig(x + 2 * (w + ds) + dv + ds, y, w, h, t, ds, d2, mColor);
    if (div) {
        helper.DrawDiv(x + 2 * w + ds, y, 2 * ds + dv, h, dv, mColor);
    }
}
