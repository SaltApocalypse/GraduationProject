#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        cout << R"(Usage: WhileTruePrint [time]

一个重复打印数字的测试程序。默认五分钟后结束。

[time] 重复的时间，-1 代表不结束。
)";
    }

    int counter = 0;
    const int TIME_TO_END = (1 == argc ? 500 : atoi(argv[1]));

    while (true)
    {
        if (TIME_TO_END > 0 && TIME_TO_END == counter)
            return 0;

        cout << "Counter is " << ++counter << endl;
        sleep(1);
    }
}