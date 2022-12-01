#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>
#include <unordered_map>

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

    std::array<int, 4> basins = {0, 0, 0, 0};

    for (uint y = 0; y < map.size(); y++)
    {
        for (uint x = 0; x < map[y].size(); x++)
        {
            if (is_lowest(map, x, y))
            {
                std::queue<std::pair<int, int>> q;
                std::unordered_map<int, std::unordered_map<int, bool>> visited;

                int counter = 1;

                visited[x][y] = true;
                q.push({x, y - 1});
                q.push({x, y + 1});
                q.push({x - 1, y});
                q.push({x + 1, y});

                while (!q.empty())
                {
                    std::pair<int, int> top = q.front();
                    q.pop();

                    if (top.first < 0 || top.second < 0 || top.second >= map.size() || top.first >= map[top.second].size())
                    {
                        continue;
                    }

                    if (map[top.second][top.first] == 9)
                    {
                        continue;
                    }

                    if (visited[top.first][top.second])
                    {
                        continue;
                    }

                    counter++;
                    q.push({top.first, top.second - 1});
                    q.push({top.first, top.second + 1});
                    q.push({top.first + 1, top.second});
                    q.push({top.first - 1, top.second});

                    visited[top.first][top.second] = true;
                }

                basins[3] = counter;
                std::sort(basins.rbegin(), basins.rend());
            }
        }
    }

    std::cout << basins[0] * basins[1] * basins[2] << '\n';

    return 0;
}