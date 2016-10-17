#include "filemonitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#ifndef _MSC_VER
#include <unistd.h>
#include <sys/time.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof (inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))
#endif

//
// FileMonitor
//
FileMonitor::FileMonitor()
{
#ifndef _MSC_VER
    mHandle = inotify_init();
#endif
}

FileMonitor::~FileMonitor()
{
#ifndef _MSC_VER
    for (auto & file : mWatchList) {
        inotify_rm_watch(mHandle, file.first);
    }
    close(mHandle);
#endif
}

void FileMonitor::AddWatch(const std::string & fileName)
{
#ifndef _MSC_VER
    int fileId = inotify_add_watch(mHandle, fileName.c_str(), IN_DELETE_SELF | IN_MODIFY | IN_MOVE_SELF);
    mWatchList.push_back(std::pair<int, const std::string>(fileId, fileName));
#endif
}

bool FileMonitor::GetFileName(int id, std::string & fileName)
{
    for (auto & p : mWatchList) {
        if (p.first == id) {
            fileName = p.second;
            return true;
        }
    }
    return false;
}

std::vector<std::string> FileMonitor::Update()
{
    std::vector<std::string> result;
#ifndef _MSC_VER
    timeval ttw;
    ttw.tv_sec = 0;
    ttw.tv_usec = 0;
    fd_set rfds;
    FD_ZERO (&rfds);
    FD_SET (mHandle, &rfds);
    if (select(FD_SETSIZE, &rfds, NULL, NULL, &ttw) > 0) {
        char buffer[BUF_LEN];
        int length = read(mHandle, buffer, BUF_LEN);
        if (length >= 0) {
            int i = 0;
            while (i < length) {
                inotify_event * event = (inotify_event*)&buffer[i];
                if (event->wd) {
                    std::string fileName;
                    if (GetFileName(event->wd, fileName)) {
                        result.push_back(fileName);
                    }
                }
                i += EVENT_SIZE + event->len;
            }
        }
    }
#endif
    return result;
}
