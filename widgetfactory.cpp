#include "Widget.h"
#include "WidgetFactory.h"
#include "json/json.h"

WidgetFactory::Node * WidgetFactory::mNodeFirst = nullptr;

WidgetFactory::WidgetFactory(const std::string & alias)
: mAlias(alias)
{
    AddFactory(this);
}

WidgetFactory::~WidgetFactory()
{
}

void WidgetFactory::AddFactory(WidgetFactory * WidgetFactory)
{
    WidgetFactory->mSelf.factory = WidgetFactory;
    WidgetFactory->mSelf.next = mNodeFirst;
    mNodeFirst = &WidgetFactory->mSelf;
}

WidgetFactory * WidgetFactory::GetFirst()
{
    return mNodeFirst->factory;
}

WidgetFactory * WidgetFactory::GetNext(WidgetFactory * widgetFactory)
{
    for (auto it = mNodeFirst; it; it = it->next) {
        if (it->factory == widgetFactory) {
            if (auto next = it->next) {
                return next->factory;
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Widget> WidgetFactory::CreateInstance(const std::string & alias)
{
    for (auto it = mNodeFirst; it; it = it->next) {
        if (it->factory->mAlias == alias) {
            return it->factory->CreateInstance();
        }
    }
    return std::shared_ptr<Widget>();
}

std::shared_ptr<Widget> WidgetFactory::CreateInstance(const Json::Value & data)
{
    std::shared_ptr<Widget> result = CreateInstance(data["type"].asString());
    result->Init(data);
    return result;
}
