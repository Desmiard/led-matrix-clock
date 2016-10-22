#include "preset.h"
#include "conditionfactory.h"

//
// Preset
//
Preset::Preset()
{
}

Preset::Preset(const Json::Value & config)
{
    Init(config);
}

Preset::~Preset()
{
}

void Preset::Init(const Json::Value & config)
{
    mName = config["name"].asString();
    const Json::Value & pages(config["pages"]);
    for (Json::Value::ArrayIndex i = 0; i < pages.size(); i++) {
        const Json::Value & pageConfig(pages.get(i, Json::Value::null));
        mPageList.push_back(std::make_shared<Page>(pageConfig));
    }
    const Json::Value & condition(config["condition"]);
    if (condition.type() == Json::objectValue) {
        mCondition = ConditionFactory::CreateInstance(condition);
    }
}

bool Preset::Test() const
{
    if (mCondition) {
        return mCondition->Test();
    }
    return false;
}

void Preset::Activate()
{
    SetPage(mPageList.front());

}

void Preset::Deactivate()
{
}

void Preset::SetPage(std::shared_ptr<Page> page)
{
    mTimer = 0;
    mCurrentPage = page;
}

std::shared_ptr<Page> Preset::GetNextPage(std::shared_ptr<Page> page)
{
    std::vector<std::shared_ptr<Page>>::iterator next = mPageList.end();
    for (auto it = mPageList.begin(); it != mPageList.end(); ++it) {
        if ((*it) == page) {
            next = it;
            break;
        }
    }
    if (next != mPageList.end()) {
        ++next;
    }
    if (next != mPageList.end()) {
        return (*next);
    }
    return mPageList.front();
}

void Preset::UpdatePage(int msec)
{
    if (!mCurrentPage) {
        if (!mPageList.empty()) {
            mCurrentPage = mPageList.front();
        }
    }
    mTimer += msec;
    if (mCurrentPage) {
        if (mPageList.size() > 1 && mCurrentPage->Duration() >= 0 && mTimer > mCurrentPage->Duration() * 1000) {
            SetPage(GetNextPage(mCurrentPage));
        }
    }
}

void Preset::Update(int msec)
{
    UpdatePage(msec);
    if (mCurrentPage) {
        mCurrentPage->Update(msec);
    }
}

void Preset::Draw(Bitmap & bitmap)
{
    if (mCurrentPage) {
        mCurrentPage->Draw(bitmap);
    }
}
