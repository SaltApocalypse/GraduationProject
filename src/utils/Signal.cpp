#include <signal.h>
#include <unistd.h>
#include <iostream>

namespace Signal
{
    /**
     * @brief 关闭信号和IO，单独处理退出信号
     */
    void closeSignal()
    {
        for (int i = 0; i < 64; i++)
        {
            signal(i, SIG_IGN);
            close(i);
        }
    }

    void test()
    {
        std::cout << "Signal included." << std::endl;
    }
}