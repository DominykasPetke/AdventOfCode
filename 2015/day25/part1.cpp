#include <fstream>
#include <iostream>
#include <array>

std::pair<uint, uint> input_data()
{
    std::ifstream in("input");
    std::string t;

    std::pair<uint, uint> pair;

    in >> t >> t >> t >> t >> t >> t >> t >> t >> t >> t >> t >> t >> t >> t >> t;
    in >> pair.first;
    in >> t >> t;
    in >> pair.second;

    return pair;
}

uint64_t get_position(uint64_t row, uint64_t column)
{
    uint64_t answer = 0;

    for (uint64_t i = 1; i <= column; i++)
    {
        answer += i;
    }

    for (uint64_t i = 1; i < row; i++)
    {
        answer += column;
        column++;
    }

    return answer;
}

int main()
{
    std::pair<uint, uint> input = input_data();

    uint64_t code = 20151125;
    uint64_t position = (get_position(input.first, input.second) % 16777196) - 1;
    // 16777196 is the amount of times it takes until the code loops around again

    for (uint64_t i = 0; i < position; i++)
    {
        code = (code * 252533) % 33554393;
    }

    std::cout << code << '\n';

    return 0;
}