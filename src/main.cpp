#include <string>

#include "spdlog/spdlog.h"

int main()
{
    // 设置日志级别为 debug（默认是 info）
    spdlog::set_level(spdlog::level::debug);

    // 输出不同级别的日志
    spdlog::debug("This is a debug message.");
    spdlog::info("This is an info message.");
    spdlog::warn("This is a warning message.");
    spdlog::error("This is an error message.");
    spdlog::critical("This is a critical message.");

    // 格式化日志
    // int number = 42;
    std::string teriri = "teriri";
    spdlog::info("The answer to life, the universe, and everything is {}.", teriri);

    return 0;
}