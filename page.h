#ifndef __PAGE_H
#define __PAGE_H

#include <string>
#include <vector>
#include <memory>
#include "bitmap.h"
#include "widget.h"
#include "json/json.h"

//
// Page
//
class Page
{
    int mDuration;

    std::string mName;
    std::vector<std::shared_ptr<Widget>> mWidgetList;
public:
    Page();
    Page(const Json::Value & config);
    ~Page();

    void Init(const Json::Value & config);
    void Update(int msec);
    void Draw(Bitmap & bitmap);


    void Reset();

    inline const std::string & Name() const { return mName; }
    inline int Duration() const { return mDuration; }
};


#endif//__PAGE_H

