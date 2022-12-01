#include <iostream>
#include <fstream>
#include <map>

int main()
{
    std::ifstream in("input");
    std::string line;

    in >> line;

    uint length = line.length();
    std::map<char, uint> frequencies[length];

    do
    {
        for (uint i = 0; i < length; i++)
        {
            frequencies[i][line[i]]++;
        }
        
    } while (in >> line);

    for (uint i = 0; i < length; i++)
    {
        std::pair<char, uint> max = {0, 0};

        for (auto j : frequencies[i])
        {
            if (max.second < j.second)
            {
                max = j;
            }
        }

        std::cout << max.first;
    }

    std::cout << '\n';

    return 0;
}