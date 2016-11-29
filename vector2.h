#ifndef __VECTOR2_H
#define __VECTOR2_H

#include <stdint.h>
#include "json/json-forwards.h"

//
// Vector2
//
class Vector2
{
private:
    int mX;
    int mY;

public:
    inline Vector2(): mX(0), mY(0) {}
    inline Vector2(int x, int y): mX(x), mY(y) {}
    inline Vector2(const Vector2 & rh) { (*this) = rh; }
    inline ~Vector2() {}

    inline Vector2 & operator=(const Vector2 & rh) { mX = rh.mX; mY = rh.mX; return (*this); }

    inline bool operator==(const Vector2 & rh) const { return (mX == rh.mX && mY == rh.mY); }
    inline bool operator!=(const Vector2 & rh) const { return (mX != rh.mX || mY != rh.mY); }

    inline int & X() { return mX; }
    inline int & Y() { return mY; }

    inline int X() const { return mX; }
    inline int Y() const { return mY; }

    static Vector2 FromJson(const Json::Value & val);

    static const Vector2 zero;
};

#endif//__VECTOR2_H
