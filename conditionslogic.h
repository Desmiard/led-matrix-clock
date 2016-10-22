#ifndef __CONDITIONSLOGIC_H
#define __CONDITIONSLOGIC_H

#include "condition.h"
#include <memory>
#include <vector>

//
// ConditionOr
// 
class ConditionOr
: public Condition
{
private:
    std::vector<std::shared_ptr<Condition>> mChild;

public:
    virtual void Init(const Json::Value & data) override;
    virtual bool Test() const override;
};

//
// ConditionAnd
//
class ConditionAnd
: public Condition
{
private:
    std::vector<std::shared_ptr<Condition>> mChild;

public:
    virtual void Init(const Json::Value & data) override;
    virtual bool Test() const override;
};

//
// ConditionNot
//
class ConditionNot
: public Condition
{
private:
    std::shared_ptr<Condition> mChild;

public:
    virtual void Init(const Json::Value & data) override;
    virtual bool Test() const override;
};

#endif//__CONDITIONSLOGIC_H