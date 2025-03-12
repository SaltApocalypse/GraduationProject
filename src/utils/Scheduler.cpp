#include "Scheduler.hpp"

using namespace Scheduler;

Heartbeat *Heartbeat::m_instance = nullptr;

Heartbeat::Heartbeat(const std::string &name, int timeout)
    : m_name(name), m_timeout(timeout), m_pid(getpid()), m_running(false), m_shm(nullptr), m_processInfo(nullptr)
{
    // 注册实例
    m_instance = this;

    // 注册信号处理函数
    std::signal(SIGINT, Heartbeat::handle_exit);
    std::signal(SIGTERM, Heartbeat::handle_exit);

    initSharedMemory();
}

void Heartbeat::initSharedMemory()
{
    // 初始化共享内存
    m_shm = new boost::interprocess::managed_shared_memory(boost::interprocess::open_or_create, SHARED_MEMORY_NAME.c_str(), SHARED_MEMORY_SIZE, nullptr, boost::interprocess::permissions(0666));
    // 构造进程信息对象（key 为进程名）
    m_processInfo = m_shm->construct<ProcessInfo>(m_name.c_str())(m_pid, m_name.c_str(), m_timeout, std::time(nullptr));
}

void Heartbeat::start()
{
    m_running = true;
    while (m_running)
    {
        {
            boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(m_processInfo->m_mutex);
            std::time(&m_processInfo->m_lastTime);
            std::cout << m_processInfo->m_id << "\t" << m_processInfo->m_name << "\t"
                      << m_processInfo->m_timeout << "\t" << m_processInfo->m_lastTime << std::endl;
        }
        sleep(m_timeout >> 1);
    }
}

void Heartbeat::stop()
{
    m_running = false;
    cleanup();
}

void Heartbeat::cleanup()
{
    if (m_shm && m_processInfo)
    {
        m_shm->destroy<ProcessInfo>(m_name.c_str());
    }
    if (m_shm)
    {
        delete m_shm;
        m_shm = nullptr;
    }
}

Heartbeat::~Heartbeat()
{
    stop();
    m_instance = nullptr;
}

void Heartbeat::handle_exit(int signal)
{
    if (m_instance)
        m_instance->stop();

    exit(0);
}
