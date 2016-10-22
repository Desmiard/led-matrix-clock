#ifndef __CONDITIONDATETIME_H
#define __CONDITIONDATETIME_H

#include "condition.h"
#include <time.h>

//
// ConditionTime
//
class ConditionTime
: public Condition
{
private:
    tm mStart;
    tm mStop;

public:
    virtual void Init(const Json::Value & data) override;
    virtual bool Test() const override;
};

//
// ConditionWeekDay
//
class ConditionWeekDay
: public Condition
{
private:
    uint8_t mWeekdayMask;
public:
    virtual void Init(const Json::Value & data) override;
    virtual bool Test() const override;
};

//
// ConditionDate
//
class ConditionDate
: public Condition
{
public:
    virtual void Init(const Json::Value & data) override;
    virtual bool Test() const override;
};

//
// ConditionSeason
//
class ConditionSeason
    : public Condition
{
public:
    virtual void Init(const Json::Value & data) override;
    virtual bool Test() const override;
};

#endif//__CONDITIONDATETIME_H
