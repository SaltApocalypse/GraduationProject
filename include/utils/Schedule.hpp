#pragma once

#include <csignal>
#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace Schedule
{
    // 常量信息
    const std::string SHARED_MEMORY_NAME = "Process"; // 共享内存名称
    const size_t SHARED_MEMORY_SIZE = 16384;          // NOTE: sizeof(ProcessInfo) * 100 ~= 16KB

    /**
     * @brief 进程信息结构体
     */
    struct ProcessInfo
    {
        int m_id = 0;                                    // 进程 ID
        int m_timeout = 0;                               // 超时
        time_t m_lastTime = 0;                           // 上次心跳时间
        boost::interprocess::string m_name = "";         // 进程名称，这里是 boost::interprocess::string
        boost::interprocess::interprocess_mutex m_mutex; // 互斥锁

        /**
         * @brief 默认构造函数
         */
        ProcessInfo() = default;

        /**
         * @brief 构造函数
         * @param id 进程 ID
         * @param _name 进程名称
         * @param _timeout 超时时间
         * @param _lastTime 上次心跳时间
         */
        ProcessInfo(int id, const char *name, int timeout, time_t lastTime)
            : m_id(id), m_timeout(timeout), m_lastTime(lastTime), m_name(name) {}

        /**
         * @brief 拷贝构造函数
         * @param other 待拷贝的对象
         */
        ProcessInfo(const ProcessInfo &other)
            : m_id(other.m_id), m_timeout(other.m_timeout), m_lastTime(other.m_lastTime), m_name(other.m_name) {}
    };

    /**
     * @brief 心跳类
     */
    class Heartbeat
    {
    public:
        Heartbeat(const std::string &name, int timeout);
        ~Heartbeat();

        /**
         * @brief 开始心跳循环
         */
        void start();

        /**
         * @brief 停止心跳循环
         */
        void stop();

    private:
        std::string m_name; // 进程名称
        int m_timeout;      // 超时时间
        int m_pid;          // 进程 ID
        bool m_running;     // 运行状态

        boost::interprocess::managed_shared_memory *m_shm = nullptr; // 共享内存指针
        ProcessInfo *m_processInfo = nullptr;                        // 进程信息指针

        static Heartbeat *m_instance; // 实例

        // 初始化共享内存和构造进程信息对象
        void initSharedMemory();

        // 清理共享内存资源
        void cleanup();

        // 静态信号处理函数，调用当前实例的stop进行清理
        static void handle_exit(int signal);
    };
}; // namespace Schedule