#ifndef __WidgetFactory_H
#define __WidgetFactory_H

#include <string>
#include <memory>
#include "json/json-forwards.h"

//
// Forward declarations
//
class Widget;

//
// WidgetFactory
//
class WidgetFactory
{
public:
    WidgetFactory(const std::string & alias);
    virtual ~WidgetFactory();

    static std::shared_ptr<Widget> CreateInstance(const std::string & alias);
    static std::shared_ptr<Widget> CreateInstance(const Json::Value & data);

private:
    static WidgetFactory * GetFirst();
    static WidgetFactory * GetNext(WidgetFactory * widgetFactory);

    static void AddFactory(WidgetFactory * widgetFactory);

    virtual std::shared_ptr<Widget> CreateInstance() const = 0;

private:
    struct Node
    {
        WidgetFactory * factory;
        Node       * next;
    };

private:
    std::string   mAlias;
    Node          mSelf;
    static Node * mNodeFirst;
};

//
// WidgetFactoryCustom
//
template <class T>
class WidgetFactoryCustom
    : public WidgetFactory
{
public:
    WidgetFactoryCustom(const std::string & alias): WidgetFactory(alias) {};
    virtual std::shared_ptr<Widget> CreateInstance() const override { return std::make_shared<T>(); }
};

#define REGISTER_WIDGET(widget, alias) WidgetFactoryCustom<widget> __factory##widget##_##alias(#alias)


#endif//__WidgetFactory_H
