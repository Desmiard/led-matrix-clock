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
    std::string mName;
    std::vector<std::shared_ptr<Widget>> mWidgetList;
public:
    Page();
    Page(const Json::Value & config);
    ~Page();

    void Init(const Json::Value & config);
    void Update();
    void Draw(Bitmap & bitmap);
};


#endif//__PAGE_H

