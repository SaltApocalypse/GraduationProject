#include <iostream>
#include <string>

#include "utils/Signal.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        std::cerr << R"(Usage: scheduler <time> </path/to/exec> [args] ...

程序调度模块：
周期性启动服务程序或 shell 脚本，被启动的程序在结束后会在 <time> 秒后被重启。

<time> 程序的循环周期，单位：秒。如果是要常驻内存的程序，请把 <time> 设置为小于5秒。
</path/to/exec> 执行的程序。
[args] ... 程序的参数。
)";
        return -1;
    }

    // Signal::closeSignal();
    Signal::test();

    return 0;
}
