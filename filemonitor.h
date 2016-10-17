#ifndef __FILEMONITRO_H
#define __FILEMONITRO_H

#include <string>
#include <vector>
#include <utility>

//
// FileMonitor
//
class FileMonitor final
{
private:
    int mHandle;
    std::vector<std::pair<int, std::string>> mWatchList;

    bool GetFileName(int id, std::string & fileName);

public:
    FileMonitor();
    ~FileMonitor();

    void AddWatch(const std::string & fileName);

    std::vector<std::string> Update();
};

#endif//__FILEMONITRO_H
