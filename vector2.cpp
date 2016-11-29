#include "vector2.h"
#include "json/json.h"

//
// Vector2
//
const Vector2 Vector2::zero;

Vector2 Vector2::FromJson(const Json::Value & val)
{
    Vector2 p;
    if (val.isObject()) {
        if (val["x"].isInt() && val["y"].isInt()) {
            p.X() = val["x"].asInt();
            p.Y() = val["y"].asInt();
        } else if (val["w"].isInt() && val["h"].isInt()) {
            p.X() = val["w"].asInt();
            p.Y() = val["h"].asInt();
        } else if (val["width"].isInt() && val["height"].isInt()) {
            p.X() = val["width"].asInt();
            p.Y() = val["height"].asInt();
        }
    }
    return p;
}
