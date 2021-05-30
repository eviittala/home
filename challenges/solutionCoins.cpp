#include <gtest/gtest.h>

#include <iostream>
namespace
{
constexpr uint64_t twoEuros{200};
uint64_t result{0};

template <typename T>
void solution(uint64_t base, T arg)
{
    for (uint64_t i{0}; (i * arg) <= twoEuros && base <= twoEuros; ++i)
    {
        if ((base + i * arg) == twoEuros)
        {
            ++result;
        }
    }
}

template <typename T, typename... Args>
void solution(uint64_t base, T arg, Args... args)
{
    for (uint64_t i{0}; (i * arg) <= twoEuros && base <= twoEuros; ++i)
    {
        base += i * arg;
        solution(base, args...);
        base -= i * arg;
    }
}

TEST(Coins, first)
{
    uint64_t base{0};
    solution(base, 1, 2, 5, 10, 20, 50, 100, 200);
    std::cout<<"Output: "<<result<<std::endl;
}
}
