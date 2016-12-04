#include "progressbar.h"
#include "widgetfactory.h"
#include "datasourcefactory.h"
#include "json/json.h"
#include <math.h>

//
// ProgressBar
//
REGISTER_WIDGET(ProgressBar, progress_bar);

ProgressBar::ProgressBar()
    : mMinValue(0)
    , mMaxValue(0)
    , mIsVertical(false)
    , mDirection(Normal)
    , mShadowEnabled(false)
{
}

void ProgressBar::Init(const Json::Value & config)
{
    mPosition = Vector2::FromJson(config["position"]);
    mSize = Vector2::FromJson(config["size"]);
    mDataSource = DataSourceFactory::CreateInstance(config["source"]);
    mColor = Color::FromJson(config["color"]);

    auto value = config["value"];
    if (value.isObject()) {
        mMinValue = value["min"].asInt();
        mMaxValue = value["max"].asInt();
    }

    if (config["direction"].isString()) {
        auto dir = config["direction"].asString();
        if (dir == "normal") {
            mDirection = Normal;
        } else if (dir == "inverse") {
            mDirection = Inverse;
        } else if (dir == "center") {
            mDirection = Center;
        }
    }

    if (config["align"].isString()) {
        std::string align = config["align"].asString();
        mIsVertical = (align == "vertical" || align == "v");
    }

    const Json::Value & shadow = config["shadow"];
    if (shadow.isObject()) {
        mShadowEnabled = true;
        mShadowColor = Color::FromJson(shadow["color"]);
        mShadowOffset = Vector2::FromJson(shadow["offset"]);
    }
}

void ProgressBar::Draw(Bitmap & bmp)
{
    int value = mMinValue;
    std::shared_ptr<NumericDataSource> nds = std::dynamic_pointer_cast<NumericDataSource>(mDataSource);
    if (nds) {
        value = nds->GetData();
    }

    double progress = static_cast<double>(value - mMinValue) / static_cast<double>(mMaxValue - mMinValue);

    int x = mPosition.X();
    int y = mPosition.Y();
    int w = mSize.X();
    int h = mSize.Y();

    if (mIsVertical) {
        int ph = (int)round(progress * h);
        switch (mDirection) {
        case Normal:
            break;
        case Inverse:
            y = y + h - ph;
            break;
        case Center:
            y = y + (h - ph) / 2;
            break;
        }
        h = ph;
    } else {
        int pw = (int)round(progress * w);
        switch (mDirection) {
        case Normal:
            break;
        case Inverse:
            x = x + w - pw;
            break;
        case Center:
            x = x + (w - pw) / 2;
            break;
        }
        w = pw;
    }
    if (mShadowEnabled) {
        bmp.Rectangle(x + mShadowOffset.X(), y + mShadowOffset.Y(), w, h, mShadowColor);
    }
    bmp.Rectangle(x, y, w, h, mColor);
}
