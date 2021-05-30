#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <random>

#include "Timer.hpp"

//python 20
//Todo list, iota


void sort(uint64_t* begin, uint64_t* end)
{
    bool run = true;
    while (run)
    {
        run = false;
        for (uint64_t* next = begin; next != end - 1; ++next)
        {
            if (*next > *(next + 1))
            {
                run = true;
                std::swap(*next, *(next + 1));
            }
        }
    }
}

uint64_t unique(uint64_t* begin, uint64_t* end)
{
    uint64_t* next = begin;
    uint64_t elemsAdded{0};
    while (++begin != end)
    {
        if (*next < *begin)
        {
            std::swap(*++next, *begin);
            ++elemsAdded;
        }
    }

    return elemsAdded + 1;
}

int main(int args, char* argv[])
{
    Timer startTimer;
    uint64_t array[] = {1, 17, 4, 3, 3, 4, 2, 4, 6, 1, 17};
    sort(array, array + 11);
    const uint64_t N = unique(array, array + 11);
    for (uint64_t i{0}; i < N; ++i)
    {
        std::cout<<array[i];
        if (i < N - 1)
            std::cout<<", ";
    }
    std::cout<<std::endl;

    return 0;
}
