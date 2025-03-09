#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <signal.h>
#include <unistd.h>

namespace Signal
{
    /**
     * @brief 关闭信号和IO，单独处理退出信号
     */
    void closeSignal();

    void test();
} // namespace Signal

#endif // SIGNAL_HPP