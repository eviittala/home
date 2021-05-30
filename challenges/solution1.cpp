#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <regex>
#include <vector>

#include "Timer.hpp"

const std::vector<std::bitset<9>> lcdNumbers {
    0b010101111,
    0b000001001,
    0b010011110,
    0b010011011,
    0b000111001,
    0b010110011,
    0b010110111,
    0b010001001,
    0b010111111,
    0b010111011};

const std::vector<std::bitset<9>> lcdPlusMinus {
    0b000011000,
    0b000010000,
    0b000010010
};

void printU(const std::bitset<9> bits, const uint8_t startBit)
{
    if (bits.test(startBit))
    {
        std::cout<<"|";
    }
    else
    {
        std::cout<<" ";
    }
    if (bits.test(startBit - 1))
    {
        std::cout<<"_";
    }
    else
    {
        std::cout<<" ";
    }
    if (bits.test(startBit - 2))
    {
        std::cout<<"|";
    }
    else
    {
        std::cout<<" ";
    }
}

std::vector<std::bitset<9>> changeValueToBits(const int arg)
{
    if (arg > 9)
    {
        std::vector<std::bitset<9>> bits = changeValueToBits(arg/10);
        bits.push_back(lcdNumbers.at(arg % 10));
        return bits;
    }
    else
    {
        std::vector<std::bitset<9>> bits;
        bits.push_back(lcdNumbers.at(arg));
        return bits;
    }
}

void printLcd(const std::vector<int> vals, const std::vector<char> plusMinus)
{
    auto getLcdPlusMinusIndex { [] (const char& arg) {
        return arg == '+' ? 0 : arg == '-' ? 1 : 2;
    }};
    auto getValuesInBits{ [] (const int& arg) {
        std::vector<std::bitset<9>> retBits = changeValueToBits(std::abs(arg));
        if (arg < 0)
        {
            retBits.resize(retBits.size() + 1);
            std::move_backward(std::begin(retBits), std::end(retBits) - 1, std::end(retBits));
            retBits.front() = lcdPlusMinus.at(1);
        }
        return retBits;
    }};
    try
    {
        for (uint64_t line{0}; line < 3; ++line)
        {
            for (uint64_t val{0}; val < vals.size(); ++val)
            {
                const uint8_t startBit = 8 - line * 3;

                auto valuesInBitsVec = getValuesInBits(vals.at(val));
                for (auto valuesInBits : valuesInBitsVec)
                {
                    printU(valuesInBits, startBit);
                }
                if (val < plusMinus.size())
                {
                    const std::bitset<9> plusMinusBits = lcdPlusMinus.at(getLcdPlusMinusIndex(plusMinus.at(val)));
                    printU(plusMinusBits, startBit);
                }
            }
            std::cout<<std::endl;
        }
    }catch(const std::out_of_range& e)
    {
        std::cout<<"Invalid values "<<e.what()<<std::endl;
    }
}

int calculateResult(const std::vector<int>& values, const std::vector<char>& plusMinus)
{
    int result{values.at(0)};
    for (uint64_t i{0}; i < plusMinus.size(); ++i)
    {
        if (plusMinus.at(i) == '+')
        {
            result += values.at(i + 1);
        }
        else
        {
            result -= values.at(i + 1);
        }
    }
    return result;
}

int main(int args, char* argv[])
{
    Timer startTimer;
    if (args < 2 )
    {
        std::cout<<"No arguments given: please try 90 + 89 - 2"<<std::endl;
        return 0;
    }
    std::vector<int> values;
    std::vector<char> plusMinus;
    for (uint64_t i{1}; i < args; ++i)
    {
        if (std::strlen(argv[i]) < 2 && std::regex_search(argv[i], std::regex(R"(\-|\+)")))
        {
            if (argv[i][0] == '+')
                plusMinus.push_back('+');
            else if (argv[i][0] == '-')
                plusMinus.push_back('-');
        }
        else
        {
            values.push_back(std::stoi(argv[i]));
        }
    }
    values.push_back(calculateResult(values, plusMinus));
    plusMinus.push_back('=');

    for (uint64_t i{0}; i < values.size(); ++i)
    {
        const char factor = i < plusMinus.size() ? plusMinus.at(i) : ' ';
        std::cout<<values.at(i)<<" "<<factor<<" ";
    }
    std::cout<<std::endl;
    printLcd(values, plusMinus);
    std::cout<<std::endl;
    return 0;
}
