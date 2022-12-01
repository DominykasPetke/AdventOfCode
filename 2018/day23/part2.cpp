#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Nanobot
{
    int x, y, z, r;
};

struct Cube
{
    int minX, minY, minZ, maxX, maxY, maxZ;
};

bool isIn(Cube c, Nanobot n)
{
    int dx = std::max(c.minX - n.x, std::max(0, n.x - c.maxX));
    int dy = std::max(c.minY - n.y, std::max(0, n.y - c.maxY));
    int dz = std::max(c.minZ - n.z, std::max(0, n.z - c.maxZ));

    return dx + dy + dz < n.r;
}

int main()
{
    std::vector<Nanobot> bots;

    { // input
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

    Cube best = {std::max_element(bots.begin(), bots.end(), [](Nanobot const &t, Nanobot const &f) { return t.x > f.x; })->x,
                 std::max_element(bots.begin(), bots.end(), [](Nanobot const &t, Nanobot const &f) { return t.y > f.y; })->y,
                 std::max_element(bots.begin(), bots.end(), [](Nanobot const &t, Nanobot const &f) { return t.z > f.z; })->z,
                 std::max_element(bots.begin(), bots.end(), [](Nanobot const &t, Nanobot const &f) { return t.x < f.x; })->x,
                 std::max_element(bots.begin(), bots.end(), [](Nanobot const &t, Nanobot const &f) { return t.y < f.y; })->y,
                 std::max_element(bots.begin(), bots.end(), [](Nanobot const &t, Nanobot const &f) { return t.z < f.z; })->z};

    Cube a = best;
    int countA = 0;

    for (auto const &i : bots)
    {
        if (isIn(a, i))
            countA++;
    }

    //std::cout << '(' << a.minX << ',' << a.minY << ',' << a.minZ << "), (" << a.maxX << ',' << a.maxY << ',' << a.maxZ << "): " << countA << '\n';

    while (best.maxX - best.minX > 250)
    {
        int halfX = best.minX + (best.maxX - best.minX) / 2,
            halfY = best.minY + (best.maxY - best.minY) / 2,
            halfZ = best.minZ + (best.maxZ - best.minZ) / 2;

        std::vector<Cube> kubai = {{best.minX, best.minY, best.minZ, halfX, halfY, halfZ},
                                   {halfX + 1, best.minY, best.minZ, best.maxX, halfY, halfZ},
                                   {best.minX, halfY + 1, best.minZ, halfX, best.maxY, halfZ},
                                   {best.minX, best.minY, halfZ + 1, halfX, halfY, best.maxZ},
                                   {halfX + 1, halfY + 1, best.minZ, best.maxX, best.maxY, halfZ},
                                   {halfX + 1, best.minY, halfZ + 1, best.maxX, halfY, best.maxZ},
                                   {best.minX, halfY + 1, halfZ + 1, halfX, best.maxY, best.maxZ},
                                   {halfX + 1, halfY + 1, halfZ + 1, best.maxX, best.maxY, best.maxZ}};

        best = *(std::max_element(kubai.begin(), kubai.end(), [&bots](Cube const &a, Cube const &b) {
            int countA = 0;
            int countB = 0;

            for (auto const &i : bots)
            {
                if (isIn(a, i))
                    countA++;
                if (isIn(b, i))
                    countB++;
            }

            //std::cout << '(' << a.minX << ',' << a.minY << ',' << a.minZ << "), (" << a.maxX << ',' << a.maxY << ',' << a.maxZ << "): " << countA << '\n';
            //std::cout << '(' << b.minX << ',' << b.minY << ',' << b.minZ << "), (" << b.maxX << ',' << b.maxY << ',' << b.maxZ << "): " << countB << '\n';

            return countA < countB;
        }));
    }

    int dist = INT32_MAX; // r=distance
    int count = 0;

    for (int x = best.minX; x <= best.maxX; x++)
        for (int y = best.minY; y <= best.maxY; y++)
            for (int z = best.minZ; z <= best.maxZ; z++)
            {
                int c = 0;
                for (auto i : bots)
                {
                    int dx = i.x - x;
                    int dy = i.y - y;
                    int dz = i.z - z;

                    if (std::abs(dx) + std::abs(dy) + std::abs(dz) < i.r)
                        c++;
                }

                if (c > count)
                {
                    count = c;
                    dist = std::abs(x) + std::abs(y) + std::abs(z);
                }
                else if (int newd = std::abs(x) + std::abs(y) + std::abs(z); c == count && newd < dist)
                    dist = newd;
            }

    std::cout << dist << '\n';

    return 0;
}