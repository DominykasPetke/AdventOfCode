#include <iostream>
#include <fstream>
#include <bitset>
#include <regex>
#include <unordered_map>

int main()
{
    std::string line;
    std::ifstream in("input");

    std::string mask;
    std::unordered_map<uint64_t, uint64_t> memory;

    while (std::getline(in, line))
    {
        std::regex mask_regex("mask = ([X01]{36})");
        std::regex mem_regex("mem\\[(\\d+)] = (\\d+)");

        std::smatch match;

        if (std::regex_search(line, match, mask_regex))
        {
            mask = match[1];
        }
        else if (std::regex_search(line, match, mem_regex))
        {
            std::bitset<36> bits(std::stoi(match[2]));

            for (int i = 0; i < 36; i++)
            {
                switch (mask[i])
                {
                case '0':
                    bits[35 - i] = 0;
                    break;
                case '1':
                    bits[35 - i] = 1;
                default:
                    break;
                }
            }

            memory[std::stoi(match[1])] = bits.to_ulong();
        }
    }

    uint64_t sum = 0;

    for (auto i : memory)
    {
        sum += i.second;
    }

    std::cout << sum << '\n';

    return 0;
}