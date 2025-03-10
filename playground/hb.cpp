#include <unistd.h>
#include <csignal>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace bip = boost::interprocess;

// 常量信息
const std::string SHARED_MEMORY_NAME = "Process";
const size_t SHARED_MEMORY_SIZE = 16384; // NOTE: sizeof(ProcessInfo) * 100 ~= 16KB

// 进程信息结构体
struct ProcessInfo
{
    int id = 0;                    // 进程 ID
    int timeout = 0;               // 超时
    time_t lastTime = 0;           // 上次心跳时间
    bip::string name;              // 进程名称，这里是 boost::interprocess::string
    bip::interprocess_mutex mutex; // 互斥锁

    ProcessInfo() = default;
    ProcessInfo(int _id, char *_name, int _timeout, time_t _lasttime) : id(_id), name(_name), timeout(_timeout), lastTime(_lasttime) {}
    ProcessInfo(const ProcessInfo &other) : id(other.id), name(other.name), timeout(other.timeout), lastTime(other.lastTime) {}
};

bip::managed_shared_memory *g_shm = nullptr;
bip::managed_shared_memory &getShm()
{
    if (nullptr == g_shm)
        g_shm = new bip::managed_shared_memory(bip::open_or_create, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE, nullptr, bip::permissions(0666));
    return *g_shm;
}

ProcessInfo *g_processInfo = nullptr;
ProcessInfo &getProcessInfo(char *name, int timeout)
{
    if (nullptr == g_processInfo)
    {
        g_processInfo = new ProcessInfo(static_cast<int>(getpid()), name, timeout, time(nullptr));
    }
    return *g_processInfo;
}

void handle_exit(int signal)
{
    // 释放共享内存
    g_shm->destroy<ProcessInfo>(g_processInfo->name.c_str());

    exit(0);
}

int main(int argc, char *argv[])
{
    /**
     * 进程心跳模拟
     * 把进程信息写入共享内存
     * ls /dev/shm/ 查看共享内存
     */

    // 处理退出信号
    signal(SIGINT, handle_exit);
    signal(SIGTERM, handle_exit);

    // 创建共享内存
    try
    {
        bip::managed_shared_memory &shm = getShm();
        ProcessInfo &pi = getProcessInfo(argv[1], std::stoi(argv[2]));
        ProcessInfo *processInfo = shm.construct<ProcessInfo>(pi.name.c_str())(pi);

        // 链接共享内存
        while (true)
        {
            // 上锁更新心跳
            {
                bip::scoped_lock<bip::interprocess_mutex> lock(processInfo->mutex);
                std::time(&processInfo->lastTime);
                std::cout << processInfo->id << "\t" << processInfo->name << "\t" << processInfo->timeout << "\t" << processInfo->lastTime << std::endl;
            }

            sleep(processInfo->timeout >> 1); // 模拟程序执行
        }
    }
    catch (const bip::interprocess_exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}