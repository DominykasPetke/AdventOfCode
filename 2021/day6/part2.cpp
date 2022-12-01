#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <numeric>

std::size_t replace_all(std::string &inout, std::string const &what, std::string const &with)
{
    std::size_t count{};

    for (std::string::size_type pos{};
         inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count)
    {
        inout.replace(pos, what.length(), with.data(), with.length());
    }

    return count;
}

int main()
{
    std::string line;
    std::ifstream in("input");

    in >> line;
    replace_all(line, ",", " ");
    std::stringstream input(line);

    std::array<uint64_t, 9> data = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int number;

    while (input >> number)
    {
        data[number]++;
    }

    for (int i = 0; i < 256; i++)
    {
        uint64_t zeros = data[0];

        for (int ix = 1; ix < 9; ix++)
        {
            data[ix - 1] = data[ix];
        }

        data[6] += zeros;
        data[8] = zeros;
    }

    uint64_t sum = std::accumulate(data.begin(), data.end(), 0UL);

    std::cout << sum << '\n';

    return 0;
}