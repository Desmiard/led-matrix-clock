#include "condition.h"
#include "conditionfactory.h"
#include "json/json.h"

ConditionFactory::Node * ConditionFactory::mNodeFirst = nullptr;

ConditionFactory::ConditionFactory(const std::string & alias)
: mAlias(alias)
{
    AddFactory(this);
}

ConditionFactory::~ConditionFactory()
{
}

void ConditionFactory::AddFactory(ConditionFactory * consditionFactory)
{
    consditionFactory->mSelf.factory = consditionFactory;
    consditionFactory->mSelf.next    = mNodeFirst;
    mNodeFirst = &consditionFactory->mSelf;
}

ConditionFactory * ConditionFactory::GetFirst()
{
    return mNodeFirst->factory;
}

ConditionFactory * ConditionFactory::GetNext(ConditionFactory * consditionFactory)
{
    for (auto it = mNodeFirst; it; it = it->next) {
        if (it->factory == consditionFactory) {
            if (auto next = it->next) {
                return next->factory;
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Condition> ConditionFactory::CreateInstance(const std::string & alias)
{
    for (auto it = mNodeFirst; it; it = it->next) {
        if (it->factory->mAlias == alias) {
            return it->factory->CreateInstance();
        }
    }
    return std::shared_ptr<Condition>();
}

std::shared_ptr<Condition> ConditionFactory::CreateInstance(const Json::Value & data)
{
    std::shared_ptr<Condition> result = CreateInstance(data["type"].asString());
    result->Init(data);
    return result;
}