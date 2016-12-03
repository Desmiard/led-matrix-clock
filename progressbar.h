#ifndef __PROGRESSBAR_H
#define __PROGRESSBAR_H

#include "widget.h"
#include "datasource.h"
#include "vector2.h"
#include <memory>

//
// ProgressBar
//
class ProgressBar
: public Widget
{
private:

    bool mInverseDirection;
    bool mIsVertical;

    Vector2 mPosition;
    Vector2 mSize;

    Color mColor;

    int mMinValue;
    int mMaxValue;

    bool mShadowEnabled;
    Vector2 mShadowOffset;
    Color mShadowColor;

    std::shared_ptr<DataSource> mDataSource;

public:
    ProgressBar();

    virtual void Init(const Json::Value & config) override;
    virtual void Draw(Bitmap & bitmap) override;
};

#endif//__PROGRESSBAR_H
