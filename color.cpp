#include "color.h"
#include "json/json.h"

const Color Color::black(0u, 0u, 0u);
const Color Color::white(255u, 255u, 255u);
const Color Color::red(255u, 0u, 0u);
const Color Color::green(0u, 255u, 0u);
const Color Color::blue(0u, 0u, 255u);
const Color Color::yellow(255u, 255u, 255u);
const Color Color::cyan(0u, 255u, 255u);
const Color Color::magenta(255u, 0u, 255u);

Color Color::FromJson(const Json::Value & val)
{
    Color c;
    if (val.isObject() && val["r"].isInt() && val["g"].isInt() && val["b"].isInt()) {
        c.R() = static_cast<uint8_t>(val["r"].asInt());
        c.G() = static_cast<uint8_t>(val["g"].asInt());
        c.B() = static_cast<uint8_t>(val["b"].asInt());
    }
    return c;
}
