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
        mMinValue = value["max"].asInt();
    }

    if (config["inverse"].isBool()) {
        mInverseDirection = config["inverse"].asBool();
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

    float progress = static_cast<float>(value - mMinValue) / static_cast<float>(mMaxValue - mMinValue);

    int x = mPosition.X();
    int y = mPosition.Y();
    int w = mSize.X();
    int h = mSize.Y();

    if (mIsVertical) {
        int ph = (int)roundf(progress * h);
        if (mInverseDirection) {
            y = y + h - ph;
        } else {
            h = ph;
        }
    } else {
        int pw = (int)roundf(progress * w);
        if (mInverseDirection) {
            x = x + w - pw;
        } else {
            w = pw;
        }
    }

    if (mShadowEnabled) {
        bmp.Rectangle(x + mShadowOffset.X(), y +  mShadowOffset.Y(), w, h, mColor);
    }
    bmp.Rectangle(x, y, w, h, mColor);
}
