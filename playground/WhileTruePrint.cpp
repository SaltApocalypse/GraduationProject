#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        cout << R"(Usage: WhileTruePrint [time]

一个重复打印数字的测试程序。默认五分钟后结束。

[time] 执行时间，单位为秒。-1 代表永久执行。
)";
    }

    int counter = 0;
    const int TIME_TO_END = (1 == argc ? 5 * 60 : stoi(argv[1]));

    while (true)
    {
        if (TIME_TO_END == counter)
            return 0;

        cout << "Counter is " << ++counter << endl;
        sleep(1);
    }
}