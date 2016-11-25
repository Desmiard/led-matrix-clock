#ifndef __CLOCKDIGITSHELPER_H
#define __CLOCKDIGITSHELPER_H

#include "color.h"
#include "bitmap.h"

//
// ClockDigitsHelper
//
class ClockDigitsHelper
{
private:
    Bitmap & mBitmap;
public:
    ClockDigitsHelper(Bitmap & bitmap): mBitmap(bitmap) {}

    void DrawSeg(int x, int y, int w, int h, int t, uint8_t m, const Color & c);
    void DrawDig(int x, int y, int w, int h, int t, uint8_t v, const Color & c);
    void DrawVSeg(int x, int y, int w, int h, const Color & c);
    void DrawHSeg(int x, int y, int w, int h, const Color & c);
    void Draw2Dig(int x, int y, int w, int h, int t, int s, uint8_t v, const Color & c);
    void DrawDiv(int x, int y, int w, int h, int t, const Color & c);
};

#endif//__CLOCKDIGITSHELPER_H
