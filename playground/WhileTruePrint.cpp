#include <unistd.h>
#include <iostream>
#include <string>
#include "Logger.hpp"
#include "Scheduler.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (static_cast<string>(argv[1]) == "-h" || static_cast<string>(argv[1]) == "--help")
    {
        cout << R"(Usage: WhileTruePrint [time] [log]

一个重复打印数字的测试程序。默认五分钟后结束。

[time] 执行时间，单位为秒。-1 代表永久执行。
[log] 是否输出日志。默认 0 不输出。
)";
        return 0;
    }
    // Scheduler::Heartbeat hb("WhileTruePrint", 5);
    // hb.start();

    int counter = 0;
    const int TIME_TO_END = (argc > 1 ? stoi(argv[1]) : 5 * 60);
    const bool IS_LOG = (argc > 2 ? stoi(argv[2]) : 0);

    auto logger = Logger::LoggerManager("WhileTruePrint");

    while (true)
    {
        if (TIME_TO_END == counter)
            return 0;

        cout << "Counter is " << ++counter << endl;

        if (IS_LOG)
        {
            logger.info("Counter is " + to_string(counter));
            logger.warn("Counter is " + to_string(counter));
            logger.error("Counter is " + to_string(counter));
            logger.debug("Counter is " + to_string(counter));
        }

        sleep(1);
    }
}