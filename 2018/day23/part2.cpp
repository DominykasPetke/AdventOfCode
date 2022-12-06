#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Nanobot
{
    int x, y, z, r;
};

struct Cube
{
    int minX, minY, minZ, maxX, maxY, maxZ;
};

struct QueueElement
{
    Cube cube;
    int count;

    bool operator<(const QueueElement &other) const
    {
        if (count == other.count)
        {
            return std::min(std::abs(cube.minX), std::abs(cube.maxX)) +
                       std::min(std::abs(cube.minY), std::abs(cube.maxY)) +
                       std::min(std::abs(cube.minZ), std::abs(cube.maxZ)) >
                   std::min(std::abs(other.cube.minX), std::abs(other.cube.maxX)) +
                       std::min(std::abs(other.cube.minY), std::abs(other.cube.maxY)) +
                       std::min(std::abs(other.cube.minZ), std::abs(other.cube.maxZ));
        }
        else
        {
            return count < other.count;
        }
    }
};

int how_many_reach_cube(const Cube &cube, const std::vector<Nanobot> &bots)
{
    return std::count_if(bots.begin(), bots.end(), [&cube](const Nanobot &bot)
                         {
                             if (bot.x + bot.r <= cube.maxX && bot.x + bot.r >= cube.minX && bot.y >= cube.minY && bot.y <= cube.maxY && bot.z >= cube.minZ && bot.z <= cube.maxZ)
                             {
                                 return true;
                             }

                             if (bot.x - bot.r <= cube.maxX && bot.x - bot.r <= cube.minX &&  bot.y >= cube.minY && bot.y <= cube.maxY && bot.z >= cube.minZ && bot.z <= cube.maxZ)
                             {
                                 return true;
                             }

                             if (bot.y + bot.r >= cube.minY && bot.y + bot.r >= cube.maxY && bot.x >= cube.minX && bot.x <= cube.maxX && bot.z >= cube.minZ && bot.z <= cube.maxZ)
                             {
                                 return true;
                             }

                             if (bot.y - bot.r <= cube.maxY && bot.y - bot.r <= cube.minY && bot.x >= cube.minX && bot.x <= cube.maxX && bot.z >= cube.minZ && bot.z <= cube.maxZ)
                             {
                                 return true;
                             }
                             
                             if (bot.z + bot.r >= cube.minZ && bot.z + bot.r >= cube.maxZ && bot.x >= cube.minX && bot.x <= cube.maxX && bot.y >= cube.minY && bot.y <= cube.maxY)
                             {
                                 return true;
                             }

                             if (bot.z - bot.r <= cube.maxZ && bot.z - bot.r <= cube.minZ && bot.x >= cube.minX && bot.x <= cube.maxX && bot.y >= cube.minY && bot.y <= cube.maxY)
                             {
                                 return true;
                             }

                             if ((std::min(std::abs(bot.x -cube.minX), std::abs(bot.x - cube.maxX)) + 
                             std::min(std::abs(bot.y -cube.minY), std::abs(bot.y - cube.maxY)) + 
                             std::min(std::abs(bot.z -cube.minZ), std::abs(bot.z - cube.maxZ))) <= bot.r) {
                                return true;
                             }

                             return false; });
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

    Cube best = {std::max_element(bots.begin(), bots.end(), [](const Nanobot &t, const Nanobot &f)
                                  { return t.x > f.x; })
                     ->x,
                 std::max_element(bots.begin(), bots.end(), [](const Nanobot &t, const Nanobot &f)
                                  { return t.y > f.y; })
                     ->y,
                 std::max_element(bots.begin(), bots.end(), [](const Nanobot &t, const Nanobot &f)
                                  { return t.z > f.z; })
                     ->z,
                 std::max_element(bots.begin(), bots.end(), [](const Nanobot &t, const Nanobot &f)
                                  { return t.x < f.x; })
                     ->x,
                 std::max_element(bots.begin(), bots.end(), [](const Nanobot &t, const Nanobot &f)
                                  { return t.y < f.y; })
                     ->y,
                 std::max_element(bots.begin(), bots.end(), [](const Nanobot &t, const Nanobot &f)
                                  { return t.z < f.z; })
                     ->z};

    std::priority_queue<QueueElement> p_queue;

    p_queue.push(QueueElement{best, how_many_reach_cube(best, bots)});

    while (!p_queue.empty())
    {
        QueueElement top = p_queue.top();
        p_queue.pop();

        if (top.cube.maxX == top.cube.minX && top.cube.maxY == top.cube.minY && top.cube.maxZ == top.cube.minZ)
        {
            std::cout << top.cube.minX + top.cube.minY + top.cube.minZ << '\n';

            return 0;
        }

        // divide into 8
        int midX = (top.cube.minX + top.cube.maxX) / 2;
        int midY = (top.cube.minY + top.cube.maxY) / 2;
        int midZ = (top.cube.minZ + top.cube.maxZ) / 2;

        Cube cube = {top.cube.minX, top.cube.minY, top.cube.minZ, midX, midY, midZ};
        int count = how_many_reach_cube(cube, bots);

        if (count > 0)
        {
            p_queue.push(QueueElement{cube, count});
        }

        if (midZ != top.cube.maxZ)
        {
            cube = {top.cube.minX, top.cube.minY, midZ + 1, midX, midY, top.cube.maxZ};
            count = how_many_reach_cube(cube, bots);

            if (count > 0)
            {
                p_queue.push(QueueElement{cube, count});
            }
        }

        if (midY != top.cube.maxY)
        {
            cube = {top.cube.minX, midY + 1, top.cube.minZ, midX, top.cube.maxY, midZ};
            count = how_many_reach_cube(cube, bots);

            if (count > 0)
            {
                p_queue.push(QueueElement{cube, count});
            }
        }

        if (midY != top.cube.maxY && midZ != top.cube.maxZ)
        {
            cube = {top.cube.minX, midY + 1, midZ + 1, midX, top.cube.maxY, top.cube.maxZ};
            count = how_many_reach_cube(cube, bots);

            if (count > 0)
            {
                p_queue.push(QueueElement{cube, count});
            }
        }

        if (midX != top.cube.maxX)
        {
            cube = {midX + 1, top.cube.minY, top.cube.minZ, top.cube.maxX, midY, midZ};
            count = how_many_reach_cube(cube, bots);

            if (count > 0)
            {
                p_queue.push(QueueElement{cube, count});
            }
        }

        if (midX != top.cube.maxX && midZ != top.cube.maxZ)
        {
            cube = {midX + 1, top.cube.minY, midZ + 1, top.cube.maxX, midY, top.cube.maxZ};
            count = how_many_reach_cube(cube, bots);

            if (count > 0)
            {
                p_queue.push(QueueElement{cube, count});
            }
        }

        if (midX != top.cube.maxX && midY != top.cube.maxY)
        {
            cube = {midX + 1, midY + 1, top.cube.minZ, top.cube.maxX, top.cube.maxY, midZ};
            count = how_many_reach_cube(cube, bots);

            if (count > 0)
            {
                p_queue.push(QueueElement{cube, count});
            }
        }

        if (midX != top.cube.maxX && midY != top.cube.maxY && midZ != top.cube.maxZ)
        {
            cube = {midX + 1, midY + 1, midZ + 1, top.cube.maxX, top.cube.maxY, top.cube.maxZ};
            count = how_many_reach_cube(cube, bots);

            if (count > 0)
            {
                p_queue.push(QueueElement{cube, count});
            }
        }
    }

    return 0;
}