#include "conditionslogic.h"
#include "conditionfactory.h"
#include "json/json.h"

//
// ConditionOr
// 
REGISTER_CONDITION(ConditionOr, or);

void ConditionOr::Init(const Json::Value & data)
{
    const Json::Value & child = data["child"];
    for (Json::Value::ArrayIndex i = 0; i < child.size(); ++i) {
        mChild.push_back(ConditionFactory::CreateInstance(child.get(i, Json::Value::null)));
    }
}

bool ConditionOr::Test() const
{
    for (auto it : mChild) {
        if (it->Test()) {
            return true;
        }
    }
    return false;
}

//
// ConditionAnd
//
REGISTER_CONDITION(ConditionAnd, and);

void ConditionAnd::Init(const Json::Value & data)
{
    const Json::Value & child = data["child"];
    for (Json::Value::ArrayIndex i = 0; i < child.size(); ++i) {
        mChild.push_back(ConditionFactory::CreateInstance(child.get(i, Json::Value::null)));
    }
}

bool ConditionAnd::Test() const
{
    for (auto it : mChild) {
        if (!it->Test()) {
            return false;
        }
    }
    return true;
}

//
// ConditionNot
//
REGISTER_CONDITION(ConditionNot, not);

void ConditionNot::Init(const Json::Value & data)
{
    mChild = ConditionFactory::CreateInstance(data["child"]);
}

bool ConditionNot::Test() const
{
    if (mChild) {
        return !mChild->Test();
    }
    return true;
}