#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <random>

#include "Timer.hpp"

//python 20
//Todo
//1. change text

std::tuple<int64_t, int64_t, int64_t, int64_t> findLimitValues(const std::vector<std::tuple<int64_t, int64_t, int64_t,
        int64_t>>& pointsVec)
{
    int64_t lowX{0};
    int64_t highX{0};
    int64_t lowY{0};
    int64_t highY{0};
    for (auto& [x1, y1, x2, y2] : pointsVec)
    {
        if (x1 < lowX)
        {
            lowX = x1;
        }
        if (x2 > highX)
        {
            highX = x2;
        }
        if (y1 < lowY)
        {
            lowY = y1;
        }
        if (y2 > highY)
        {
            highY = y2;
        }
    }
    return {lowX, lowY, highX, highY};
}

int64_t isInArea(const std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>>& pointsVec, const int64_t x, const
        int64_t y)
{
    int64_t ret{0};
    for (auto& [x1, y1, x2, y2] : pointsVec)
    {
        if (x1 <= x && x2 > x && y1 <= y && y2 > y)
        {
            //std::cout<<x<<", "<<y<<" x2: "<<x2<<std::endl;
            if (x2 - x > ret)
                ret = x2 - x;
        }
    }
   return ret;
}

//bool canAdvanceX(const std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>>& pointsVec, const int64_t xMin, const
//        int64_t xMax)
//{
//    for (auto& [x1, y1, x2, y2] : pointsVec)
//    {
//       if (
//    }
//    return true;
//}

uint64_t calculateArea(const std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>>& pointsVec)
{
    const auto [lowX, lowY, highX, highY] = findLimitValues(pointsVec);
    uint64_t retArea{0};

    for (int64_t y{lowY}; y < highY; ++y)
    {
        for (int64_t x{lowX}; x < highX; ++x)
        {
            if (const int64_t xAdvance = isInArea(pointsVec, x, y))
            {
                //std::cout<<"advance: "<<xAdvance<<std::endl;
                retArea += xAdvance;
                x += xAdvance - 1;
            }
        }
    }

    return retArea;
}

void printVec(std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> points)
{
    for (uint64_t i{0}; i < points.size(); ++i)
    {
        auto& [x1, y1, x2, y2] = points.at(i);
        std::cout<<"Rectangle "<<i<<": ("<<x1<<", "<<y1<<"), ("<<x2<<", "<<y2<<")"<<std::endl;
    }
}

int main(int args, char* argv[])
{
    {
        std::cout<<"Test 1"<<std::endl;
        Timer startTimer;
        std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> points {{0, 0, 4, 3}, {3, -1, 6, 3}, {5, 1, 7, 4}};
        printVec(points);
        std::cout<<"Area: "<<calculateArea(points)<<std::endl;
    }
    {
        std::cout<<std::endl<<"Test 2"<<std::endl;
        Timer startTimer;
        std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> points {{0, 0, 6, 3}, {1, -1, 2, 3}, {0, 1, 6, 3}};
        printVec(points);
        std::cout<<"Area: "<<calculateArea(points)<<std::endl;
    }
    {
        std::cout<<std::endl<<"Test 3"<<std::endl;
        Timer startTimer;
        std::vector<std::tuple<int64_t, int64_t, int64_t, int64_t>> points {{0, 0, 1000000, 1000000}, {0, 1, 1000000,
            2}, {0, 1000000 - 1, 1, 1000000}};
        printVec(points);
        std::cout<<"Area: "<<calculateArea(points)<<std::endl;
    }
    return 0;
}
/*
Test 1
Rectangle 0: (0, 0), (4, 3)
Rectangle 1: (3, -1), (6, 3)
Rectangle 2: (5, 1), (7, 4)
Area: 25
Test elapsed: 0.001996000s

Test 2
Rectangle 0: (0, 0), (6, 3)
Rectangle 1: (1, -1), (2, 3)
Rectangle 2: (0, 1), (6, 3)
Area: 19
Test elapsed: 0.001994000s

Test 3
Rectangle 0: (0, 0), (100000, 100000)
Rectangle 1: (0, 1), (100000, 2)
Rectangle 2: (0, 99999), (1, 100000)
Area: 10000000000
Test elapsed: 18.875454000s

*/
