#include "Logger.hpp"

using namespace Logger;

LoggerManager *LoggerManager::m_instance = nullptr;

LoggerManager::LoggerManager(const std::string &logName,
                             const std::string &logFolder,
                             size_t logMaxSize,
                             bool enableBuffer,
                             int mode)
    : m_logName(logName),
      m_logFolder(logFolder),
      m_logMaxSize(logMaxSize),
      m_enableBuffer(enableBuffer),
      m_mode(mode)
{
    if (m_instance)
        return;

    // 注册实例
    m_instance = this;

    try
    {
        std::vector<spdlog::sink_ptr> sinks;

        if (mode & LOG_MODE_CONSOLE)
            sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        if (mode & LOG_MODE_FILE)
        {
            spdlog::flush_every(std::chrono::seconds(5));
            spdlog::flush_on(spdlog::level::debug);
            sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFolder + logName + ".log", logMaxSize, 10));
        }

        if (enableBuffer)
        {
            spdlog::init_thread_pool(BUFFER_SIZE, 1);
            m_logger = std::make_shared<spdlog::async_logger>(
                logName,
                sinks.begin(), sinks.end(),
                spdlog::thread_pool(),
                spdlog::async_overflow_policy::block);
        }
        else
        {
            m_logger = std::make_shared<spdlog::logger>(logName, sinks.begin(), sinks.end());
        }

        m_logger->set_level(spdlog::level::debug);
        spdlog::register_logger(m_logger);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        spdlog::error("Logger initialization failed: {}", ex.what());
        m_instance = nullptr;
    }
}

LoggerManager::~LoggerManager()
{
    m_logger->flush();
    spdlog::drop(m_logName);
    spdlog::shutdown();
    m_logger = nullptr;
}

void LoggerManager::info(const std::string &msg) { m_logger->info(msg); }
void LoggerManager::warn(const std::string &msg) { m_logger->warn(msg); }
void LoggerManager::error(const std::string &msg) { m_logger->error(msg); }
void LoggerManager::debug(const std::string &msg) { m_logger->debug(msg); }