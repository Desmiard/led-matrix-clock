#include "ClockDigitsHelper.h"

inline bool TestBit(int bit, uint8_t mask) { return ((mask & 1 << bit) != 0); }

//
// ClockDigitsHelper
//
void ClockDigitsHelper::DrawSeg(int x, int y, int w, int h, int t, uint8_t m, const Color & c)
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

    if (TestBit(0, m)) DrawVSeg(xv1, yv1, t, hv, c);
    if (TestBit(2, m)) DrawVSeg(xv2, yv1, t, hv, c);
    if (TestBit(4, m)) DrawVSeg(xv1, yv2, t, hv, c);
    if (TestBit(5, m)) DrawVSeg(xv2, yv2, t, hv, c);
    if (TestBit(1, m)) DrawHSeg(xh, yh1, wh, t, c);
    if (TestBit(3, m)) DrawHSeg(xh, yh2, wh, t2, c);
    if (TestBit(6, m)) DrawHSeg(xh, yh3, wh, t, c);
}

void ClockDigitsHelper::DrawDig(int x, int y, int w, int h, int t, uint8_t v, const Color & c)
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
    DrawSeg(x, y, w, h, t, tt[v], c);
}

void ClockDigitsHelper::DrawVSeg(int x, int y, int w, int h, const Color & c)
{
    int f = (w - 1) / 2;
    int m = w - 2 * f;
    for (int i = 0; i < f; ++i) {
        int k = f - i;
        mBitmap.LineV(x + i, y + k, h - 2 * k, c);
    }
    for (int i = 0, o = f; i < m; ++i) {
        mBitmap.LineV(x + i + o, y, h, c);
    }
    for (int i = 0, o = f + m; i < f; ++i) {
        int k = i + 1;
        mBitmap.LineV(x + i + o, y + k, h - 2 * k, c);
    }
}

void ClockDigitsHelper::DrawHSeg(int x, int y, int w, int h, const Color & c)
{
    int f = (h - 1) / 2;
    int m = h - 2 * f;
    for (int i = 0; i < f; ++i) {
        int k = f - i;
        mBitmap.LineH(x + k, y + i, w - 2 * k, c);
    }
    for (int i = 0, o = f; i < m; ++i) {
        mBitmap.LineH(x, y + i + o, w, c);
    }
    for (int i = 0, o = f + m; i < f; ++i) {
        int k = i + 1;
        mBitmap.LineH(x + k, y + i + o, w - 2 * k, c);
    }
}

void ClockDigitsHelper::Draw2Dig(int x, int y, int w, int h, int t, int s, uint8_t v, const Color & c)
{
    DrawDig(x, y, w, h, t, (v / 10) % 10, c);
    DrawDig(x + s + w, y, w, h, t, (v % 10), c);
}

void ClockDigitsHelper::DrawDiv(int x, int y, int w, int h, int t, const Color & c)
{
    int t2 = t + (w - t) % 2;
    int px = x + (w - t2) / 2;

    int q = t2 + h % 2;

    int y0 = y + h / 2;
    int y1 = y0 - t2 - t2;
    int y2 = y0 + q;

    mBitmap.Rectangle(px, y1, t2, t2, c);
    mBitmap.Rectangle(px, y2, t2, t2, c);
}
