#include "digitaldisplay.h"
#include "ClockDigitsHelper.h"
#include "widgetfactory.h"
#include "datasourcefactory.h"
#include "json/json.h"

//
// DigitalDisplay
//
REGISTER_WIDGET(DigitalDisplay, digital_display);

DigitalDisplay::DigitalDisplay()
: mColor(0, 32, 32)
, mPosition(0, 2)
, mSize(14, 29)
, mThickness(3)
, mSpace(1)
, mDivider(3)
{
}

DigitalDisplay::~DigitalDisplay()
{
}

void DigitalDisplay::Draw(Bitmap & bitmap)
{
    std::shared_ptr<NumericDataSource> nds = std::dynamic_pointer_cast<NumericDataSource>(mDataSource);
    if (nds) {
        DrawDisplay(bitmap, nds->GetData());
    }
}

void DigitalDisplay::DrawDisplay(Bitmap & bitmap, int val)
{
    ClockDigitsHelper helper(bitmap);

    int x = mPosition.X();
    int y = mPosition.Y();
    int w = mSize.X();
    int h = mSize.Y();
    int t = mThickness;
    int ds = mSpace;

    switch (mDigits) {
    case 1:
        if (mShadowEnabled) {
            helper.DrawDig(x + mShadowOffset.X(), y + mShadowOffset.Y(), w, h, t, val % 10, mShadowColor);
        }
        helper.DrawDig(x + mShadowOffset.X(), y + mShadowOffset.Y(), w, h, t, val % 10, mShadowColor);
        break;

    case 2:
        if (mShadowEnabled) {
            helper.Draw2Dig(x + mShadowOffset.X(), y + mShadowOffset.Y(), w, h, t, ds, val % 100, mShadowColor);
        }
        helper.Draw2Dig(x, y, w, h, t, ds, val, mColor);
        break;

    case 3:
        break;

    case 4:
        break;
    }
}

void DigitalDisplay::Init(const Json::Value & config)
{
    mPosition = Vector2::FromJson(config["position"]);
    mColor = Color::FromJson(config["color"]);
    mSize = Vector2::FromJson(config["options"]);

    const Json::Value & options = config["options"];
    mThickness = options["thickness"].asInt();
    mSpace = options["space"].asInt();
    mDigits = options["digits"].asInt();

    mDataSource = DataSourceFactory::CreateInstance(config["source"]);

    const Json::Value & shadow = config["shadow"];
    if (shadow.isObject()) {
        mShadowEnabled = true;
        mShadowColor = Color::FromJson(shadow["color"]);
        mShadowOffset = Vector2::FromJson(shadow["offset"]);
    }
}
