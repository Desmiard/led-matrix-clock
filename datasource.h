#ifndef __DATASOURCE_H
#define __DATASOURCE_H

#include "json/json-forwards.h"

//
// DataSource
//
class DataSource
{
public:
    virtual ~DataSource() {}
    virtual void Init(const Json::Value & data) = 0;
};

//
// NumericDataSource
//
class NumericDataSource
: public DataSource
{
public:
    virtual int GetData() const = 0;
};

#endif//__DATASOURCE_H
