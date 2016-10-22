#include "basicclock.h"
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
}

void BasicClock::Draw(Bitmap & bitmap)
{
    time_t t = time(NULL);
#ifdef _MSC_VER
    tm ti;
    localtime_s(&ti, &t);
#else
    tm ti = (*localtime(&t));
#endif
    DrawClock(bitmap, mX, mY, mWidth, mHeight, mThickness, mSpace, mDivider, (uint8_t)ti.tm_hour, (uint8_t)ti.tm_min, ti.tm_sec % 2 == 1);
}

void BasicClock::DrawVSeg(Bitmap & bitmap, int x, int y, int w, int h)
{
    int f = (w - 1) / 2;
    int m = w - 2 * f;
    for (int i = 0; i < f; ++i) {
        int k = f - i;
        bitmap.LineV(x + i, y + k, h - 2 * k, mColor);
    }
    for (int i = 0, o = f; i < m; ++i) {
        bitmap.LineV(x + i + o, y, h, mColor);
    }
    for (int i = 0, o = f + m; i < f; ++i) {
        int k = i + 1;
        bitmap.LineV(x + i + o, y + k, h - 2 * k, mColor);
    }
}

void BasicClock::DrawHSeg(Bitmap & bitmap, int x, int y, int w, int h)
{
    int f = (h - 1) / 2;
    int m = h - 2 * f;
    for (int i = 0; i < f; ++i) {
        int k = f - i;
        bitmap.LineH(x + k, y + i, w - 2 * k, mColor);
    }
    for (int i = 0, o = f; i < m; ++i) {
        bitmap.LineH(x, y + i + o, w, mColor);
    }
    for (int i = 0, o = f + m; i < f; ++i) {
        int k = i + 1;
        bitmap.LineH(x + k, y + i + o, w - 2 * k, mColor);
    }
}

inline bool TestBit(int bit, uint8_t mask) { return ((mask & 1 << bit) != 0); }

void BasicClock::DrawDig(Bitmap & bitmap, int x, int y, int w, int h, int t, uint8_t v)
{
    const uint8_t tt[] = {
        0x77, // 0
        0x24, // 1
        0x5E, // 2
        0x6E, // 3
        0x2D, // 4
        0x6B, // 5
        0x7B, // 6
        0x26, // 7
        0x7F, // 8
        0x6F, // 9
    };
    DrawSeg(bitmap, x, y, w, h, t, tt[v]);
}

void BasicClock::DrawSeg(Bitmap & bitmap, int x, int y, int w, int h, int t, uint8_t m)
{
    int t2 = t + (h - 3 * t) % 2;

    int f = (t - 1) / 2;
    int f2 = (t2 - 1) / 2;

    int tf = t - f;
    int thm = t2 - 2 * f2;

    int hv = (h - (tf + tf + thm)) / 2;
    int yv1 = y + tf;
    int yv2 = yv1 + hv + thm;

    int xv1 = x;
    int xv2 = x + w - t;

    int xh = x + tf;
    int wh = w - 2 * tf;
    int yh1 = y;
    int yh2 = y + (h - t2) / 2;
    int yh3 = y + h - t;

    if (TestBit(0, m)) DrawVSeg(bitmap, xv1, yv1, t, hv);
    if (TestBit(2, m)) DrawVSeg(bitmap, xv2, yv1, t, hv);
    if (TestBit(4, m)) DrawVSeg(bitmap, xv1, yv2, t, hv);
    if (TestBit(5, m)) DrawVSeg(bitmap, xv2, yv2, t, hv);
    if (TestBit(1, m)) DrawHSeg(bitmap, xh, yh1, wh, t);
    if (TestBit(3, m)) DrawHSeg(bitmap, xh, yh2, wh, t2);
    if (TestBit(6, m)) DrawHSeg(bitmap, xh, yh3, wh, t);
}

void BasicClock::Draw2Dig(Bitmap & bitmap, int x, int y, int w, int h, int t, int s, uint8_t v)
{
    DrawDig(bitmap, x, y, w, h, t, (v / 10) % 10);
    DrawDig(bitmap, x + s + w, y, w, h, t, (v % 10));
}

void BasicClock::DrawDiv(Bitmap & bitmap, int x, int y, int w, int h, int t)
{
    int t2 = t + (w - t) % 2;
    int px = x + (w - t2) / 2;

    int q = t2 + h % 2;

    int y0 = y + h / 2;
    int y1 = y0 - t2 - t2;
    int y2 = y0 + q;

    bitmap.Rectangle(px, y1, t2, t2, mColor);
    bitmap.Rectangle(px, y2, t2, t2, mColor);
}

void BasicClock::DrawClock(Bitmap & bitmap, int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div)
{
    Draw2Dig(bitmap, x, y, w, h, t, ds, d1);
    Draw2Dig(bitmap, x + 2 * (w + ds) + dv + ds, y, w, h, t, ds, d2);
    if (div) {
        DrawDiv(bitmap, x + 2 * w + ds, y, 2 * ds + dv, h, dv);
    }
}
