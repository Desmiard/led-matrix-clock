#include "colorrect.h"
#include "widgetfactory.h"

//
// ColorRect
//
REGISTER_WIDGET(ColorRect, color_rect);

ColorRect::ColorRect()
: mColor(Color::black)
, mX(0)
, mY(0)
, mWidth(0)
, mHeight(0)
{
}

void ColorRect::Draw(Bitmap & bitmap)
{
    bitmap.Rectangle(mX, mY, mWidth, mHeight, mColor);
}

void ColorRect::Init(const Json::Value & config)
{
    const Json::Value & position = config["position"];
    mX = position["x"].asInt();
    mY = position["y"].asInt();

    const Json::Value & color = config["color"];
    mColor.R() = (uint8_t)color["r"].asInt();
    mColor.G() = (uint8_t)color["g"].asInt();
    mColor.B() = (uint8_t)color["b"].asInt();

    const Json::Value & options = config["size"];
    mWidth = options["width"].asInt();
    mHeight = options["height"].asInt();
}
