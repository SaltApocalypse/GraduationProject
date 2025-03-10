#include <iostream>
#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
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

int main(int argc, char *argv[])
{
    if (argc < 2)
        return std::cerr << R"(Usage: ./test "process_name")" << std::endl, -1;

    std::string targetName = argv[1];

    try
    {
        bip::managed_shared_memory shm(bip::open_only, SHARED_MEMORY_NAME.c_str());

        // 查找所有可能的进程信息
        std::pair<ProcessInfo *, std::size_t> result;
        result = shm.find<ProcessInfo>(targetName.c_str());

        if (result.first)
        {
            ProcessInfo *info = result.first;

            // 在加锁之前检查 mutex 是否已经被其他线程占用
            {
                bip::scoped_lock<bip::interprocess_mutex> lock(info->mutex);
                std::cout << info->id << "\t" << info->name << "\t" << info->timeout << "\t" << info->lastTime << std::endl;
            }

            return 0;
        }
        else
        {
            std::cerr << "ProcessInfo not found!" << std::endl;
            return -1;
        }
    }
    catch (const bip::interprocess_exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
