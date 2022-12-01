#include <iostream>
#include <fstream>
#include <vector>
#include <array>

int main()
{
    std::string line;
    std::vector<std::array<int, 2>> data;

    std::ifstream in("input");
    in >> line;

    data.reserve(line.size());

    for (unsigned int i = 0; i < line.size(); i++)
    {
        data.push_back({0, 0});
    }

    do
    {
        for (unsigned int i = 0; i < line.size(); i++)
        {
            switch (line[i])
            {
            case '0':
                data[i][0]++;
                break;
            case '1':
                data[i][1]++;

            default:
                break;
            }
        }
    } while (in >> line);

    int gamma = 0;
    int epsilon = 0;

    for (auto a : data)
    {
        if (a[0] > a[1])
        {
            gamma <<= 1;
            epsilon <<= 1;
            epsilon += 1;
        }
        else
        {
            gamma <<= 1;
            epsilon <<= 1;
            gamma += 1;
        }
    }

    std::cout << gamma * epsilon << '\n';

    return 0;
}