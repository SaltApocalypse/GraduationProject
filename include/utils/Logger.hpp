#pragma once

#include <csignal>
#include <memory>
#include <string>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>

namespace Logger
{
    const std::string LOG_FOLDER = "./logs/";      // 默认日志文件夹
    const size_t LOG_MAX_SIZE = 100 * 1024 * 1024; // 默认日志分页大小 100MB
    const size_t BUFFER_SIZE = 8192;               // 默认缓冲区大小

    const int LOG_MODE_CONSOLE = 1 << 0;                           // 控制台输出
    const int LOG_MODE_FILE = 1 << 1;                              // 文件输出
    const int LOG_MODE_DEFAULT = LOG_MODE_CONSOLE | LOG_MODE_FILE; // 默认输出

    /**
     * @brief 日志类
     */
    class LoggerManager
    {
    public:
        /**
         * @brief 获取日志管理器实例
         * @param logName 日志名称
         * @param logFolder 日志文件夹
         * @param logMaxSize 日志分页大小
         * @param enableBuffer 是否启用缓冲区
         * @param mode 日志输出模式
         */
        LoggerManager(const std::string &logName,
                      const std::string &logFolder = LOG_FOLDER,
                      size_t logMaxSize = LOG_MAX_SIZE,
                      bool enableBuffer = true,
                      int mode = LOG_MODE_DEFAULT);
        ~LoggerManager();

        void info(const std::string &msg);
        void warn(const std::string &msg);
        void error(const std::string &msg);
        void debug(const std::string &msg);

    private:
        std::shared_ptr<spdlog::logger> m_logger; // 日志对象
        std::string m_logFolder;                  // 日志文件夹
        std::string m_logName;                    // 日志名称
        size_t m_logMaxSize;                      // 日志分页大小
        bool m_enableBuffer;                      // 是否启用缓冲区
        int m_mode;                               // 日志输出模式

        static LoggerManager *m_instance; // 实例
    };
} // namespace Logger