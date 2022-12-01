#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool is_lowest(std::vector<std::vector<int>> const &map, uint x, uint y)
{
    int value = map[y][x];

    if (x == 0)
    {
        if (y == 0)
        {
            if (value >= map[y + 1][x] || value >= map[y][x + 1])
            {
                return false;
            }
        }
        else if (y == map.size() - 1)
        {
            if (value >= map[y - 1][x] || value >= map[y][x + 1])
            {
                return false;
            }
        }
        else
        {
            if (value >= map[y + 1][x] || value >= map[y - 1][x] || value >= map[y][x + 1])
            {
                return false;
            }
        }
    }
    else if (x == map[y].size() - 1)
    {
        if (y == 0)
        {
            if (value >= map[y + 1][x] || value >= map[y][x - 1])
            {
                return false;
            }
        }
        else if (y == map.size() - 1)
        {
            if (value >= map[y - 1][x] || value >= map[y][x - 1])
            {
                return false;
            }
        }
        else
        {
            if (value >= map[y + 1][x] || value >= map[y - 1][x] || value >= map[y][x - 1])
            {
                return false;
            }
        }
    }
    else
    {
        if (y == 0)
        {
            if (value >= map[y + 1][x] || value >= map[y][x - 1] || value >= map[y][x + 1])
            {
                return false;
            }
        }
        else if (y == map.size() - 1)
        {
            if (value >= map[y - 1][x] || value >= map[y][x - 1] || value >= map[y][x + 1])
            {
                return false;
            }
        }
        else
        {
            if (value >= map[y + 1][x] || value >= map[y - 1][x] || value >= map[y][x - 1] || value >= map[y][x + 1])
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{

    std::string line;
    std::ifstream in("input");

    std::vector<std::vector<int>> map;

    while (std::getline(in, line))
    {
        std::vector<int> line_info;

        for (auto c : line)
        {
            line_info.push_back(c - '0');
        }

        map.push_back(line_info);
    }

    int sum = 0;

    for (uint y = 0; y < map.size(); y++)
    {
        for (uint x = 0; x < map[y].size(); x++)
        {
            if (is_lowest(map, x, y))
            {
                sum += map[y][x] + 1;
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}