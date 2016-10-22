#include "conditiondatetime.h"
#include "conditionfactory.h"
#include "json/json.h"
#include <iomanip>


namespace
{
    inline tm ParseTime(const std::string & str)
    {
        std::tm t = {};
        std::istringstream ss(str);
        auto loc = std::locale();
#ifndef _MSC_VER
        ss.imbue(std::locale("en_US.UTF8"));
#else
        ss.imbue(std::locale());
#endif
        ss >> std::get_time(&t, "%H:%M");
        if (!ss.fail()) {

        }
        return t;
    }

    template <typename T>
    inline int Compare(const T & a, const T & b)
    {
        if (a == b) {
            return 0;
        } else if (a < b) {
            return -1;
        } else {
            return 1;
        }
    }

    inline int CompareTime(const tm & a, const tm & b)
    {
        if (int r = Compare(a.tm_hour, b.tm_hour)) {
            return r;
        }
        if (int r = Compare(a.tm_min, b.tm_min)) {
            return r;
        }
        if (int r = Compare(a.tm_sec, b.tm_sec)) {
            return r;
        }
        return 0;
    }
}

//
// ConditionTime
//
REGISTER_CONDITION(ConditionTime, time);

void ConditionTime::Init(const Json::Value & data)
{
    mStart = ParseTime(data["start"].asString());
    mStop = ParseTime(data["stop"].asString());
}

bool ConditionTime::Test() const
{
    time_t t = time(NULL);
    tm ti;
    localtime_s(&ti, &t);

    if (CompareTime(mStop, mStart) > 0) {
        return (CompareTime(ti, mStart) >= 0 && CompareTime(ti, mStop) <= 0);
    } else {
        return (CompareTime(ti, mStart) >= 0 != CompareTime(ti, mStop) <= 0);
    }    
    return false;
}


//
// ConditionWeekDay
//
REGISTER_CONDITION(ConditionWeekDay, weekday);

void ConditionWeekDay::Init(const Json::Value & data)
{

    mWeekdayMask = 0;

    const Json::Value & allow = data["allow"];
    for (Json::Value::ArrayIndex i = 0; i < allow.size(); ++i) {
        const Json::Value & v(allow.get(i, Json::Value::null));
        if (v.isString()) {
            auto s = v.asString();
            if (s == "workday" || s == "weekday") {
                mWeekdayMask |= 0x1f;
            } else if (s == "weekend") {
                mWeekdayMask |= 0x60;
            } else if (s == "monday" || s == "mo" || s == "mon") {
                mWeekdayMask |= 0x01;
            } else if (s == "tuesday" || s == "tu" || s == "tue") {
                mWeekdayMask |= 0x02;
            } else if (s == "wednesday" || s == "we" || s == "wed") {
                mWeekdayMask |= 0x04;
            } else if (s == "thursday" || s == "th" || s == "thu") {
                mWeekdayMask |= 0x08;
            } else if (s == "friday" || s == "fr" || s == "fri") {
                mWeekdayMask |= 0x10;
            } else if (s == "saturday" || s == "sa" || s == "sat") {
                mWeekdayMask |= 0x20;
            } else if (s == "sunday" || s == "su" || s == "sun") {
                mWeekdayMask |= 0x40;
            }
        }
    }
}

bool ConditionWeekDay::Test() const
{
    time_t t = time(NULL);
    tm ti;
    localtime_s(&ti, &t);
    return ((1 << (ti.tm_wday + 6) % 7) & mWeekdayMask) != 0;
}

//
// ConditionDate
//
REGISTER_CONDITION(ConditionDate, date);

void ConditionDate::Init(const Json::Value & data)
{

}

bool ConditionDate::Test() const
{
    return false;
}

//
// ConditionSeason
//
REGISTER_CONDITION(ConditionSeason, season);

void ConditionSeason::Init(const Json::Value & data)
{

}

bool ConditionSeason::Test() const
{
    return false;
}
