#include "Scheduler.hpp"

int main(int argc, char *argv[])
{
    /**
     * 进程心跳模拟
     * 把进程信息写入共享内存
     * ls /dev/shm/ 查看共享内存
     */
    Scheduler::Heartbeat hb(argv[1], std::stoi(argv[2]));
    hb.start();
    return 0;
}
