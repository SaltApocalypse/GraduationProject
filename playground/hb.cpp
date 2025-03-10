#include <unistd.h>
#include <csignal>
#include <ctime>
#include <iostream>
#include <string>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace bip = boost::interprocess;

// 常量信息
const std::string SHARED_MEMORY_NAME = "Process";
const size_t SHARED_MEMORY_SIZE = 512; // NOTE: sizeof(ProcessInfo)

// 进程信息结构体
struct ProcessInfo
{
    int id = 0;          // 进程 ID
    bip::string name;    // 进程名称，这里是 boost::interprocess::string
    int timeout = 0;     // 超时
    time_t lastTime = 0; // 上次心跳时间
};

void handle_exit(int signal)
{
    // 释放共享内存
    bip::shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
    exit(0);
}

int main()
{
    /**
     * 进程心跳模拟
     * 把进程信息写入共享内存
     */

    // 处理退出信号
    signal(SIGINT, handle_exit);
    signal(SIGTERM, handle_exit);

    // 创建共享内存
    bip::shared_memory_object::remove(SHARED_MEMORY_NAME.c_str());
    bip::managed_shared_memory shm(bip::open_or_create, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE, nullptr, bip::permissions(0666));
    ProcessInfo *processInfo = shm.construct<ProcessInfo>("ProcessInfo")();

    processInfo->id = 1;
    processInfo->name = "test";
    processInfo->timeout = -1;
    processInfo->lastTime = 0;

    std::cout << "Hello." << std::endl;

    // 链接共享内存
    while (true)
    {
        // 更新心跳
        std::cout << processInfo->id << " " << processInfo->name << " " << processInfo->timeout << " " << processInfo->lastTime << std::endl;
        sleep(1); // 模拟程序执行

        std::time(&processInfo->lastTime);
    }
}
