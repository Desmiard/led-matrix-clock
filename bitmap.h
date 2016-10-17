#ifndef __BITMAP_H
#define __BITMAP_H

#include <vector>
#ifndef _MSC_VER
#include "led-matrix.h"
#endif
#include "stdint.h"
#include "color.h"

//
// Bitmap
//
class Bitmap
{
private:
    std::vector<Color> mData;
    int mWidth;
    int mHeight;

    inline bool IsValidPoint(int x, int y) { return (0 <= x && x < mWidth) && (0 <= y && y < mHeight); }
    inline void SetPixelInt(int x, int y, const Color & c) { if (IsValidPoint(x, y)) { mData[y * mWidth + x] = c; } }

    inline Color & GetPixelInt(int x, int y) { return mData[y * mWidth + x]; }

public:
    Bitmap();
    Bitmap(int w, int h);

    void Init(int w, int h);

    void Clear();
    void Fill(const Color & c);

    void SetPixel(int x, int y, const Color & c);
    void LineV(int x, int y, int h, const Color & c);
    void LineH(int x, int y, int w, const Color & c);
    void Rectangle(int x, int y, int w, int h, const Color & c);
#ifndef _MSC_VER
    void Blt(rgb_matrix::Canvas * canvas);
#endif
    void Blt(const Bitmap & bitmap);
};

#endif //__BITMAP_H
