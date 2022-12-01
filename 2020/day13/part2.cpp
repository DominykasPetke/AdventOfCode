#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> buses;

    {
        std::string line;
        std::ifstream in("input");

        in >> line >> line;

        line = std::regex_replace(line, std::regex(","), " ");
        line = std::regex_replace(line, std::regex("x"), "1");

        std::stringstream ss(line);

        int number;

        while (ss >> number)
        {
            buses.push_back(number);
        }
    }

    uint64_t offset = std::max_element(buses.begin(), buses.end()) - buses.begin();
    uint64_t i = buses[offset] - offset;
    uint64_t count = buses[offset];
    buses[offset] = 0;

    while (1)
    {
        for (uint64_t j = 0; j < buses.size(); j++)
        {
            if (buses[j] != 0)
            {
                if ((i + j) % buses[j] == 0)
                {
                    count *= buses[j];
                    buses[j] = 0;
                }
            }
        }

        if (std::find_if_not(buses.begin(), buses.end(), [](int a) { return a == 0; }) == std::end(buses))
        {
            std::cout << i << '\n';

            return 0;
        }

        i += count;
    }
}