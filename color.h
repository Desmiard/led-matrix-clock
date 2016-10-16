#ifndef __COLOR_H
#define __COLOR_H

#include <stdint.h>

//
// Color
//
class Color final
{
private:
    uint8_t mR;
    uint8_t mG;
    uint8_t mB;

public:
    inline Color(): mR(0u), mG(0u), mB(0u) { }
    inline Color(const uint8_t r, const uint8_t g, const uint8_t b): mR(r), mG(g), mB(b) { }
    inline Color(const Color & rh) { (*this) = rh; }
    inline ~Color() {}    

    inline Color & operator=(const Color & rh) { mR = rh.mR; mG = rh.mG; mB = rh.mB; return (*this); }

    inline bool operator==(Color & rh) const { return (mR == rh.mR && mG == rh.mG && mB == rh.mB); }
    inline bool operator!=(Color & rh) const { return (mR != rh.mR || mG != rh.mG || mB != rh.mB); }

    inline uint8_t & R() { return mR; }
    inline uint8_t & G() { return mG; }
    inline uint8_t & B() { return mB; }

    inline uint8_t R() const { return mR; }
    inline uint8_t G() const { return mG; }
    inline uint8_t B() const { return mB; }

    static const Color black;
    static const Color white;
    static const Color red;
    static const Color green;
    static const Color blue;
    static const Color yellow;
    static const Color cyan;
    static const Color magenta;
};

#endif//__COLOR_H
