#include <algorithm>
#include <functional>
#include <iostream>

#include "Timer.hpp"

int main(int args, char* argv[])
{
    Timer startTimer;

    auto len{[](const char* str) -> size_t
        {
            size_t ret{0};
            while(str[ret] != '\0') ++ret;
            return ret;
        }};
    std::function<void(char*, char*)> swapStr = [&swapStr](char* b, char* e)
    {
        if (1 < e - b)
        {
            std::swap(*b++, *--e);
            swapStr(b, e);
        }
    };
    if (args > 1)
    {
        std::cout<<"Orig: "<<argv[1]<<std::endl;
        swapStr(argv[1], argv[1] + len(argv[1]));
        std::cout<<"Swapped: "<<argv[1]<<std::endl;
    }

    return 0;
}
