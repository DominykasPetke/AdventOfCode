#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

struct Nanobot
{
    int x, y, z, r;
};

int main()
{
    std::vector<Nanobot> bots;

    {
        std::ifstream in("input");

        std::string line;

        while (std::getline(in, line))
        {
            auto search = line.find(',');
            while (search != std::string::npos)
            {
                line[search] = ' ';
                search = line.find(',');
            }

            line.erase(0, line.find('<') + 1);
            int x = std::stoi(line);

            line.erase(0, line.find(' ') + 1);
            int y = std::stoi(line);

            line.erase(0, line.find(' ') + 1);
            int z = std::stoi(line);

            line.erase(0, line.find('=') + 1);
            int r = std::stoi(line);

            bots.push_back({x, y, z, r});
        }
    }

    std::vector<std::pair<Nanobot, int>> data;

    for (auto const &i : bots)
        data.push_back({i, std::count_if(bots.begin(), bots.end(), [&i](Nanobot const &a) {
                            return (std::abs(i.x - a.x) + std::abs(i.y - a.y) + std::abs(i.z - a.z)) < i.r;
                        })});

    std::sort(data.begin(), data.end(), [](std::pair<Nanobot, int> const &t, std::pair<Nanobot, int> const &f) {
        return t.second < f.second;
    });

    for (auto const &i : data)
        std::cout << '<' << i.first.x << ',' << i.first.y << ',' << i.first.z << ',' << i.first.r << ">: " << i.second << '\n';

    return 0;
}