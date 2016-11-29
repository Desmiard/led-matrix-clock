#include "datasource.h"
#include "datasourcefactory.h"
#include "json/json.h"

DataSourceFactory::Node * DataSourceFactory::mNodeFirst = nullptr;

DataSourceFactory::DataSourceFactory(const std::string & alias)
    : mAlias(alias)
{
    AddFactory(this);
}

DataSourceFactory::~DataSourceFactory()
{
}

void DataSourceFactory::AddFactory(DataSourceFactory * dataSourceFactory)
{
    dataSourceFactory->mSelf.factory = dataSourceFactory;
    dataSourceFactory->mSelf.next = mNodeFirst;
    mNodeFirst = &dataSourceFactory->mSelf;
}

DataSourceFactory * DataSourceFactory::GetFirst()
{
    return mNodeFirst->factory;
}

DataSourceFactory * DataSourceFactory::GetNext(DataSourceFactory * dataSourceFactory)
{
    for (auto it = mNodeFirst; it; it = it->next) {
        if (it->factory == dataSourceFactory) {
            if (auto next = it->next) {
                return next->factory;
            }
        }
    }
    return nullptr;
}

std::shared_ptr<DataSource> DataSourceFactory::CreateInstance(const std::string & alias)
{
    for (auto it = mNodeFirst; it; it = it->next) {
        if (it->factory->mAlias == alias) {
            return it->factory->CreateInstance();
        }
    }
    return std::shared_ptr<DataSource>();
}

std::shared_ptr<DataSource> DataSourceFactory::CreateInstance(const Json::Value & data)
{
    std::shared_ptr<DataSource> result = CreateInstance(data["type"].asString());
    result->Init(data);
    return result;
}