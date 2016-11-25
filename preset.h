#ifndef __PRESET_H
#define __PRESET_H

#include <string>
#include <vector>
#include <memory>
#include "bitmap.h"
#include "page.h"
#include "condition.h"
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
    std::shared_ptr<Condition> mCondition;

    bool mEnabled;
    int mTimer;
    std::shared_ptr<Page> GetNextPage(std::shared_ptr<Page> page);

    void SetPage(std::shared_ptr<Page> page);
    void UpdatePage(int msec);
public:
    Preset();
    Preset(const Json::Value & config);
    ~Preset();

    void Init(const Json::Value & config);
    void Update(int msec);
    void Draw(Bitmap & bitmap);

    void Activate();
    void Deactivate();

    bool Test() const;

    bool Enabled() const;

    inline const std::string & Name() const { return mName; }
};

#endif//__PRESET_H
