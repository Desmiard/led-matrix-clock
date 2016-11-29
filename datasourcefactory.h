#ifndef __DATASOURCEFACTORY_H
#define __DATASOURCEFACTORY_H

#include <string>
#include <memory>
#include "json/json-forwards.h"

//
// Forward declarations
//
class DataSource;

//
// DataSourceFactory
//
class DataSourceFactory
{
public:
    DataSourceFactory(const std::string & alias);
    virtual ~DataSourceFactory();

    static std::shared_ptr<DataSource> CreateInstance(const std::string & alias);
    static std::shared_ptr<DataSource> CreateInstance(const Json::Value & data);

private:
    static DataSourceFactory * GetFirst();
    static DataSourceFactory * GetNext(DataSourceFactory * dataSourceFactory);

    static void AddFactory(DataSourceFactory * dataSourceFactory);

    virtual std::shared_ptr<DataSource> CreateInstance() const = 0;

private:
    struct Node
    {
        DataSourceFactory * factory;
        Node       * next;
    };

private:
    std::string   mAlias;
    Node          mSelf;
    static Node * mNodeFirst;
};

//
// DataSourceFactoryCustom
//
template <class T>
class DataSourceFactoryCustom
    : public DataSourceFactory
{
public:
    DataSourceFactoryCustom(const std::string & alias): DataSourceFactory(alias) {};
    virtual std::shared_ptr<DataSource> CreateInstance() const override { return std::make_shared<T>(); }
};

#define REGISTER_DATASOURCE(datasource, alias) DataSourceFactoryCustom<datasource> __factory##datasource##_##alias(#alias)


#endif//__DATASOURCEFACTORY_H
