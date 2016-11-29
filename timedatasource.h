#ifndef __TIMEDATASOURCE_H
#define __TIMEDATASOURCE_H

#include "datasource.h"

//
//TimeDataSource
//
class TimeDataSource
: public NumericDataSource
{
public:
    enum Mode
    {
        SEC,
        MIN,
        HOUR,
        DAY,
        MONTH,
        YEAR,
    };

    Mode mMode;

public:
    TimeDataSource();

    virtual void Init(const Json::Value & data) override;
    virtual int GetData() const override;
};

#endif//__TIMEDATASOURCE_H
