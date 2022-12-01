#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>

// MD5 code taken from https://github.com/azureatom/md5
#include "md5.h"

int main()
{
    std::ifstream in("input");
    std::string line;

    in >> line;
    //line = "abc";

    int counter = 0;
    std::array<bool, 8> is_in_place{0, 0, 0, 0, 0, 0, 0, 0};
    std::string answer = "________";

    while (!std::all_of(is_in_place.begin(), is_in_place.end(), [](bool a) { return a; }))
    {
        std::string to_hash = line + std::to_string(counter);

        std::string out = md5sum(to_hash.c_str(), to_hash.length());
        uint8_t position = out[5] - '0';

        if (out.starts_with("00000") && position < 8 && !is_in_place[position])
        {
            answer[position] = out[6];
            is_in_place[position] = true;
            // std::cout << answer << '\n'; // "bonus" points
        }

        counter++;
    }

    std::cout << answer << '\n';

    return 0;
}