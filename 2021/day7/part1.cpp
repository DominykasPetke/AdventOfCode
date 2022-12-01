#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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
    std::vector<int> locations;

    {
        std::string line;
        std::ifstream in("input");

        in >> line;
        replace_all(line, ",", " ");
        std::stringstream input(line);

        int number;

        while (input >> number)
        {
            locations.push_back(number);
        }
    }

    auto minmax = std::minmax_element(locations.begin(), locations.end());

    int min = INT32_MAX;

    for (int i = (*minmax.first); i <= (*minmax.second); i++)
    {
        int sum = std::accumulate(locations.begin(), locations.end(), 0, [i](int sum, int number) -> int
                                  { return sum + std::abs(number - i); });

        if (sum < min)
        {
            min = sum;
        }
    }

    std::cout << min << '\n';

    return 0;
}