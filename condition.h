#ifndef __CONDITION_H
#define __CONDITION_H

#include "json/json-forwards.h"
#include <string>

//
// Condition
//
class Condition
{
public:
    virtual ~Condition() {};

    virtual void Init(const Json::Value & data) = 0;
    virtual bool Test() const = 0;
};

#endif//__CONDITION_H
