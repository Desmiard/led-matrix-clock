#ifndef __COLORRECT_H
#define __COLORRECT_H

#include "widget.h"

//
// ColorRect
//
class ColorRect
    : public Widget
{
private:
    Color mColor;
    int mX;
    int mY;
    int mWidth;
    int mHeight;

public:
    ColorRect();
    virtual void Draw(Bitmap & bitmap) override;
    virtual void Init(const Json::Value & config) override;
};

#endif//__COLORRECT_H

