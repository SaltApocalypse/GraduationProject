#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <iostream>
#include <string>
// #include "utils/Signal.hpp"

void closeSignal();

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << R"(Usage: Scheduler <time> </path/to/exec> [args] ...

程序调度模块：
周期性启动服务程序或 shell 脚本，被启动的程序在结束后会在 <time> 秒后被重启。

<time> 程序的循环周期，单位：秒。如果是要常驻内存的程序，请把 <time> 设置为小于5秒。
</path/to/exec> 执行的程序。
[args] ... 程序的参数。

查询相关调度：
ps -ef | grep -E "Scheduler|[exec]"
)";
        return -1;
    }

    // 检测输入
    int time = std::stoi(argv[1]);
    if (time <= 0)
        return std::cerr << "输入的时间格式不对，请输入大于零的秒数。" << std::endl, -1;

    // TODO:
    //  Signal::closeSignal();
    closeSignal();

    char *argvs[argc];
    for (int i = 2; i < argc; i++)
        argvs[i - 2] = argv[i];
    argvs[argc - 2] = NULL;

    while (true)
    {
        if (0 == fork())
        {
            // 子进程运行被调度的程序
            execv(argv[2], argvs);
            exit(0);
        }
        else
        {
            int statu;
            wait(&statu);
            sleep(time);
        }
    }

    return 0;
}

void closeSignal()
{
    // 关闭信号
    for (int i = 0; i < 64; i++)
    {
        signal(i, SIG_IGN);
        close(i);
    }

    // 生成子进程交由系统托管，不再受 shell 控制
    if (fork() != 0)
        exit(0);

    signal(SIGCHLD, SIG_DFL);
}