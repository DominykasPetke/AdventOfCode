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

                             if ((std::min(bot.x -cube.minX, bot.x - cube.maxX) + 
                             std::min(bot.y -cube.minY, bot.y - cube.maxY) + 
                             std::min(bot.z -cube.minZ, bot.z - cube.maxZ)) < bot.r) {
                                return true;
                             }

                             return false; });
}

int main()
{
    std::vector<Nanobot> bots;

    { // input
        std::ifstream in("input_t");

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
            std::cout << top.count << '\n';
            return 0;
        }

        // divide into 8

        int midX = (top.cube.minX + top.cube.maxX) / 2;
        int midY = (top.cube.minY + top.cube.maxY) / 2;
        int midZ = (top.cube.minZ + top.cube.maxZ) / 2;

        Cube cube = {top.cube.minX, top.cube.minY, top.cube.minZ, midX, midY, midZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        cube = {top.cube.minX, top.cube.minY, midZ, midX, midY, top.cube.maxZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        cube = {top.cube.minX, midY, top.cube.minZ, midX, top.cube.maxY, midZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        cube = {top.cube.minX, midY, midZ, midX, top.cube.maxY, top.cube.maxZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        cube = {midX, top.cube.minY, top.cube.minZ, top.cube.maxX, midY, midZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        cube = {midX, top.cube.minY, midZ, top.cube.maxX, midY, top.cube.maxZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        cube = {midX, midY, top.cube.minZ, top.cube.maxX, top.cube.maxY, midZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        cube = {midX, midY, midZ, top.cube.maxX, top.cube.maxY, top.cube.maxZ};
        p_queue.push(QueueElement{cube, how_many_reach_cube(cube, bots)});

        std::cout << "a\n";
    }

    return 0;
}