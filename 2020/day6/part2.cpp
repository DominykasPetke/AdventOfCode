#include <iostream>
#include <fstream>
#include <unordered_map>

int main()
{
    std::ifstream in("input");
    int sum = 0;
    std::string line;

    std::unordered_map<char, int> counts;
    int people_count = 0;

    while (std::getline(in, line))
    {
        if (line == "")
        {
            for (auto i : counts)
            {
                if (i.second == people_count)
                {
                    sum++;
                }
            }

            counts.clear();
            people_count = 0;
        }
        else
        {
            for (char c : line)
            {
                counts[c]++;
            }

            people_count++;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}