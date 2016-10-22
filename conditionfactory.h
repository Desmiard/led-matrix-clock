#ifndef __CONDITIONFACTORY_H
#define __CONDITIONFACTORY_H

#include <string>
#include <memory>
#include "json/json-forwards.h"

//
// Forward declarations
//
class Condition;

//
// ConditionFactory
//
class ConditionFactory
{
public:
    ConditionFactory(const std::string & alias);
    virtual ~ConditionFactory();

    static std::shared_ptr<Condition> CreateInstance(const std::string & alias);
    static std::shared_ptr<Condition> CreateInstance(const Json::Value & data);

private:
    static ConditionFactory * GetFirst();
    static ConditionFactory * GetNext(ConditionFactory * conditionFactory);

    static void AddFactory(ConditionFactory * conditionFactory);

    virtual std::shared_ptr<Condition> CreateInstance() const = 0;

private:
    struct Node
    {
        ConditionFactory * factory;
        Node       * next;
    };

private:
    std::string   mAlias;
    Node          mSelf;
    static Node * mNodeFirst;
};

//
// ConditionFactoryCustom
//
template <class T>
class ConditionFactoryCustom
: public ConditionFactory
{
public:
    ConditionFactoryCustom(const std::string & alias) : ConditionFactory(alias) {};
    virtual std::shared_ptr<Condition> CreateInstance() const override { return std::make_shared<T>(); }
};

#define REGISTER_CONDITION(condition, alias) ConditionFactoryCustom<condition> __factory##condition##_##alias(#alias);

#endif //__CONDITIONFACTORY_H
