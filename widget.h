#ifndef __WIDGET_H
#define __WIDGET_H

#include "bitmap.h"
#include "json/json.h"

//
// Widget
//
class Widget
{
public:
    Widget();
    virtual ~Widget();
    virtual void Update(int msec);
    virtual void Draw(Bitmap & bitmap);
    virtual void Init(const Json::Value & config);
};

#endif //__WIDGET_H
