#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct star
{
    int x, y, velX, velY;

    star() {}

    star(int const n_x, int const n_y, int const n_vX, int const n_vY)
        : x(n_x), y(n_y), velX(n_vX), velY(n_vY) {}
};

int main()
{
    std::vector<star> stars;

    {
        int x, y, vY, vX;
        std::string line;
        std::ifstream in("input");

        while (std::getline(in, line))
        {
            line.erase(0, line.find('<') + 1);
            x = std::stoi(line);

            line.erase(0, line.find(',') + 1);
            y = std::stoi(line);

            line.erase(0, line.find('<') + 1);
            vX = std::stoi(line);

            line.erase(0, line.find(',') + 1);
            vY = std::stoi(line);

            stars.push_back({x, y, vX, vY});
        }
    }

    for (int i = 0; i < 10400; i++)
    {
        for (auto &j : stars)
        {
            j.x += j.velX;
            j.y += j.velY;
        }

        if (std::all_of(stars.begin(), stars.end(), [](star const &a) { return a.x < 181 && a.x > 118 && a.y < 151 && a.y > 139; }))
            for (int y = 140; y < 150; y++)
            {
                for (int x = 119; x < 180; x++)
                    if (std::any_of(stars.begin(), stars.end(), [x, y](star const &a) { return a.x == x && a.y == y; }))
                        std::cout << '*';
                    else
                        std::cout << ' ';

                std::cout << '\n';
            }
    }

    return 0;
}