#include "preset.h"

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
}

void Preset::Update()
{
    if (!mCurrentPage) {
        if (!mPageList.empty()) {
            mCurrentPage = mPageList.front();
        }
    }
    if (mCurrentPage) {
        mCurrentPage->Update();
    }
}

void Preset::Draw(Bitmap & bitmap)
{
    if (mCurrentPage) {
        mCurrentPage->Draw(bitmap);
    }
}
