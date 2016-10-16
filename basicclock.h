#ifndef __BASIC_CLOCK_H
#define __BASIC_CLOCK_H

#include "color.h"
#include "widget.h"

//
// BasicClock
//
class BasicClock
: public Widget
{
private:
    Color mColor;
    int mX;
    int mY;

    int mWidth;
    int mHeight;

    int mThickness;
    int mSpace;
    int mDivider;

    void DrawSeg(Bitmap & bitmap, int x, int y, int w, int h, int t, uint8_t m);
    void DrawDig(Bitmap & bitmap, int x, int y, int w, int h, int t, uint8_t v);
    void DrawVSeg(Bitmap & bitmap, int x, int y, int w, int h);
    void DrawHSeg(Bitmap & bitmap, int x, int y, int w, int h);
    void Draw2Dig(Bitmap & bitmap, int x, int y, int w, int h, int t, int s, uint8_t v);
    void DrawClock(Bitmap & bitmap, int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div);
    void DrawDiv(Bitmap & bitmap, int x, int y, int w, int h, int t);

public:
    BasicClock();
    BasicClock(int x, int y, int w, int h, int t, int ds, int dv, const Color & c);

    virtual void Draw(Bitmap & bitmap) override;
};

#endif//__BASIC_CLOCK_H
