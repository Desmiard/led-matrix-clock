#include "page.h"
#include "basicclock.h"
//
// Page
//
Page::Page()
    : mDuration(-1)
{
}

Page::Page(const Json::Value & config)
{
    Init(config);
}

Page::~Page()
{
}

void Page::Init(const Json::Value & config)
{
    mName = config["name"].asString();
    mDuration = config["duration"].asInt();
    const Json::Value & widgets(config["widgets"]);
    for (Json::Value::ArrayIndex i = 0; i < widgets.size(); i++) {
        const Json::Value & widgetConfig(widgets.get(i, Json::Value::null));
        std::string type = widgetConfig["type"].asString();
        std::shared_ptr<Widget> widget;
        if (type == "basic_clock") {
            widget = std::make_shared<BasicClock>();
        }
        if (widget) {
            widget->Init(widgetConfig);
            mWidgetList.push_back(widget);
        }
    }
}

void Page::Reset()
{

}

void Page::Update(int msec)
{
    for (auto widget : mWidgetList) {
        widget->Update(msec);
    }
}

void Page::Draw(Bitmap & bitmap)
{
    for (auto widget : mWidgetList) {
        widget->Draw(bitmap);
    }
}
