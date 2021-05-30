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

using Flights = std::vector<std::pair<std::string, std::string>>;

bool isValid(Flights& fligths)
{
    for (uint64_t i{0}; i < fligths.size() - 1; ++i)
    {
        if (!(fligths.at(i).second == fligths.at(i + 1).first))
        {
            return false;
        }
    }
    return true;
}

void printFlights(Flights& flights, std::string startPlace)
{
    std::sort(std::begin(flights), std::end(flights), [](auto& arg1, auto& arg2)
            {
                return arg1.second < arg2.second;
            });
    do
    {
        if ((flights.front().first == startPlace) && isValid(flights))
        {
            std::cout<<flights.front().first;
            for (auto& i : flights)
            {
                std::cout<<" -> "<<i.second;
            }
            std::cout<<std::endl;
            return;
        }
    } while(std::next_permutation(std::begin(flights), std::end(flights), [] (auto& arg1, auto& arg2) { return
                arg1.second < arg2.second;}));
    std::cout<<"NULL"<<std::endl;
}

int main(int args, char* argv[])
{
    Timer timer;
    Flights flights1{{"SFO", "HKO"}, {"YYZ", "SFO"}, {"YUL", "YYZ"}, {"HKO", "ORD"}};
    printFlights(flights1, "YUL");

    Flights flights2{{"A", "C"}, {"A", "B"}, {"B", "C"}, {"C", "A"}};
    printFlights(flights2, "A");

    Flights flights3{{"SFO", "COM"}, {"COM", "YYZ"}};
    printFlights(flights3, "COM");
    return 0;
}
