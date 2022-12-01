#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

int main()
{

    std::string line;
    std::ifstream in("input");

    int64_t sum = 0;

    while (std::getline(in, line))
    {
        std::vector<std::string> digits;
        std::stringstream input(line);

        std::string digit;
        for (int i = 0; i < 10; i++)
        {
            input >> digit;
            std::sort(digit.begin(), digit.end());
            digits.push_back(digit);
        }

        std::sort(digits.begin(), digits.end(), [](std::string const &t, std::string const &f)
                  { return t.length() < f.length(); });

        std::map<char, char> mapping;

        // find top ('a') using the diff between 1 and 7

        for (int i = 0; i < 3; i++)
        {
            if (digits[0].find(digits[1][i]) == std::string::npos)
            {
                mapping['a'] = digits[1][i];
                break;
            }
        }

        // find top right ('c') and bottom right ('f') by counting both values of 1

        int counter = 0;
        for (int i = 0; i < 10; i++)
        {
            if (digits[i].find(digits[0][0]) != std::string::npos)
            {
                counter++;
            }
        }

        if (counter == 9)
        {
            mapping['f'] = digits[0][0];
            mapping['c'] = digits[0][1];
        }
        else
        {
            mapping['c'] = digits[0][0];
            mapping['f'] = digits[0][1];
        }

        // find 2 by finding which one doesn't have 'f' on (only one)
        // this way I'll know 'b' (the other one that's not on on 2)

        for (int i = 3; i < 6; i++)
        {
            if (digits[i].find(mapping['f']) == std::string::npos) // it's 2
            {
                for (char c = 'a'; c < 'h'; c++)
                {
                    if (c != mapping['f'] && digits[i].find(c) == std::string::npos)
                    {
                        mapping['b'] = c;
                        break;
                    }
                }

                break;
            }
        }

        // find 'd' by seeing which one letter of 4 is not in mapped

        std::string four;
        four += mapping['c'];
        four += mapping['f'];
        four += mapping['b'];

        for (int i = 0; i < 4; i++)
        {
            if (four.find(digits[2][i]) == std::string::npos)
            {
                mapping['d'] = digits[2][i];
                break;
            }
        }

        // find 'g' by seeing which one is missing from 9
        // can reuse four
        four += mapping['d'];
        four += mapping['a'];

        // 0, 6, 9 (6-8)

        for (int i = 6; i < 9; i++)
        {
            // not 0 and not 6
            if (digits[i].find(mapping['d']) != std::string::npos &&
                digits[i].find(mapping['c']) != std::string::npos)
            {
                // we 9

                for (int j = 0; j < 6; j++)
                {
                    if (four.find(digits[i][j]) == std::string::npos)
                    {
                        mapping['g'] = digits[i][j];
                        break;
                    }
                }

                break;
            }
        }

        // find 'e' by seeing which one is missing from 8
        // can reuse four
        four += mapping['g'];

        for (int j = 0; j < 7; j++)
        {
            if (four.find(digits[9][j]) == std::string::npos)
            {
                mapping['e'] = digits[9][j];
                break;
            }
        }

        const std::vector<std::string> starting = {
            "abcefg",
            "cf",
            "acdeg",
            "acdfg",
            "bdcf",
            "abdfg",
            "abdefg",
            "acf",
            "abcdefg",
            "abcdfg"};

        std::map<std::string, int> remapped;

        for (int i = 0; i < 10; i++)
        {
            std::string copy = starting[i];

            for (auto &c : copy)
            {
                c = mapping[c];
            }

            std::sort(copy.begin(), copy.end());

            remapped[copy] = i;
        }

        input >> digit; // eat the |
        int number = 0;

        for (int i = 0; i < 4; i++)
        {
            input >> digit;

            std::sort(digit.begin(), digit.end());

            number *= 10;
            number += remapped[digit];
        }

        sum += number;
    }

    std::cout << sum << '\n';

    return 0;
}