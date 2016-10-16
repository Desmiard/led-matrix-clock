#ifndef __WIDGET_H
#define __WIDGET_H

#include "bitmap.h"

//
// Widget
//
class Widget
{
public:
    Widget();
    virtual ~Widget();
    virtual void Draw(Bitmap & bitmap);
    virtual void Init();
};

#endif //__WIDGET_H
