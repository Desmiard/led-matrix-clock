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

    bool mShadowEnabled;
    int  mShadowOffsetX;
    int  mShadowOffsetY;
    Color mShadowColor;

    void DrawClock(Bitmap & bitmap, int x, int y, int w, int h, int t, int ds, int dv, uint8_t d1, uint8_t d2, bool div);

public:
    BasicClock();
    BasicClock(int x, int y, int w, int h, int t, int ds, int dv, const Color & c);

    virtual void Draw(Bitmap & bitmap) override;
    virtual void Init(const Json::Value & config) override;
};

#endif//__BASIC_CLOCK_H
