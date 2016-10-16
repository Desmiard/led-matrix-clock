#include "bitmap.h"

//
// Bitmap
//
Bitmap::Bitmap()
: mWidth(-1)
, mHeight(-1)
{
}

Bitmap::Bitmap(int w, int h)
{
    Init(w, h);
}

void Bitmap::Init(int w, int h)
{
    mWidth = w;
    mHeight = h;
    mData.clear();
    for (int i = 0, e = w * h; i < e; ++i) {
        mData.push_back(Color());
    }
}

void Bitmap::Clear()
{
    Fill(Color::black);
}

void Bitmap::Fill(const Color & c)
{
    for (auto & p : mData) {
        p = c;
    }
}

void Bitmap::SetPixel(int x, int y, const Color & c)
{
    SetPixelInt(x, y, c);
}

void Bitmap::LineV(int x, int y, int h, const Color & c)
{
    Rectangle(x, y, 1, h, c);
}

void Bitmap::LineH(int x, int y, int w, const Color & c)
{
    Rectangle(x, y, w, 1, c);
}

void Bitmap::Rectangle(int x, int y, int w, int h, const Color & c)
{
    for (int j = y, ej = y + h; j < ej; ++j) {
        for (int i = x, ei = x + w; i < ei; ++i) {
            SetPixelInt(i, j, c);
        }
    }
}

void Bitmap::Blt(rgb_matrix::Canvas * canvas)
{
    for (int j = 0, ej = canvas->height(); j < ej; ++j) {
        for (int i = 0, ei = canvas->width(); i < ei; ++i) {
            if (IsValidPoint(i, j)) {
                Color & c = GetPixelInt(i, j);
                canvas->SetPixel(i, j, c.R(), c.G(), c.B());
            }
        }
    }
}

void Bitmap::Blt(const Bitmap & bitmap)
{
    //for (int j = y, ej = y + h; j < ej; ++j) {
    //    for (int i = x, ei = x + w; i < ei; ++i) {
    //        bitmap.SetPixelInt(x
    //
    //    }
    //}
}
