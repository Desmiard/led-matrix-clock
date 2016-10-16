#ifndef __PRESET_H
#define __PRESET_H

#include <string>
#include <vector>
#include <memory>
#include "bitmap.h"
#include "page.h"
#include "json/json.h"

//
// Preset
//
class Preset final
{
private:
    std::string mName;
    std::vector<std::shared_ptr<Page>> mPageList;
    std::shared_ptr<Page> mCurrentPage;

public:
    Preset();
    Preset(const Json::Value & config);
    ~Preset();

    void Init(const Json::Value & config);
    void Update();
    void Draw(Bitmap & bitmap);
};

#endif//__PRESET_H
