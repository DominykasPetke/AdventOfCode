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

    Nanobot best = *(std::max_element(bots.begin(), bots.end(), [](Nanobot const &t, Nanobot const &f) { return t.r < f.r; }));

    std::for_each(bots.begin(), bots.end(), [&best](Nanobot &bot) {
        bot.x -= best.x;
        bot.y -= best.y;
        bot.z -= best.z;
    });

    std::cout << std::count_if(bots.begin(), bots.end(), [&best](Nanobot const &a) { return (std::abs(a.x) + std::abs(a.y) + std::abs(a.z)) <= best.r; }) << '\n';

    return 0;
}