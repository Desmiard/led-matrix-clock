#ifndef __DIGITALDISPLAY_H
#define __DIGITALDISPLAY_H

#include "color.h"
#include "vector2.h"
#include "widget.h"
#include "datasource.h"
#include <memory>

//
// DigitalDisplay
//
class DigitalDisplay
: public Widget
{
private:
    Color mColor;
    Vector2 mPosition;
    Vector2 mSize;

    int mThickness;
    int mSpace;
    int mDivider;
    int mDigits;

    bool mShadowEnabled;
    Vector2 mShadowOffset;
    Color mShadowColor;

    std::shared_ptr<DataSource> mDataSource;

    void DrawDisplay(Bitmap & bitmap, int val);

public:
    DigitalDisplay();
    ~DigitalDisplay();

    virtual void Draw(Bitmap & bitmap) override;
    virtual void Init(const Json::Value & config) override;
};

#endif//__DIGITALDISPLAY_H
