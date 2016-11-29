#include "timedatasource.h"
#include <time.h>
#include "json/json.h"
#include "datasourcefactory.h"

//
//TimeDataSource
//
REGISTER_DATASOURCE(TimeDataSource, time);

TimeDataSource::TimeDataSource()
: mMode(SEC)
{
}

void TimeDataSource::Init(const Json::Value & data)
{
    std::string mode = data["mode"].asString();
    if (mode == "sec") {
        mMode = SEC;
    } else if (mode == "min") {
        mMode = MIN;
    } else if (mode == "hour") {
        mMode = HOUR;
    } else if (mode == "day") {
        mMode = DAY;
    } else if (mode == "month") {
        mMode = MONTH;
    } else if (mode == "year") {
        mMode = YEAR;
    }
}

int TimeDataSource::GetData() const
{
    time_t t = time(NULL);
    tm ti;
#ifdef _MSC_VER
    localtime_s(&ti, &t);
#else
    ti = (*localtime(&t));
#endif
    switch (mMode) {
    case SEC:
        return ti.tm_sec;
    case MIN:
        return ti.tm_min;
    case HOUR:
        return ti.tm_hour;
    case DAY:
        return ti.tm_mday;
    case MONTH:
        return ti.tm_mon + 1;
    case YEAR:
        return ti.tm_year + 1900;
    }
    return 0;
}
