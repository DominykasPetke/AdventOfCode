#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>

struct coords
{
    int x, y, sizeX, sizeY;
};

bool read(std::ifstream &in, coords &out)
{
    std::string line;

    while (std::getline(in, line))
    {
        line = line.substr(line.find('@') + 2);
        out.x = std::stoi(line);

        line.erase(0, line.find(',') + 1);
        out.y = std::stoi(line);

        line.erase(0, line.find(' ') + 1);
        out.sizeX = std::stoi(line);

        line.erase(0, line.find('x') + 1);
        out.sizeY = std::stoi(line);

        return true;
    }

    return false;
}

int main()
{
    std::ifstream in("input");

    std::array<int, 1000 * 1000> grid;
    grid.fill(0);

    coords data;
    while (read(in, data))
        for (int i = data.x; i < data.x + data.sizeX; i++)
            for (int j = data.y; j < data.y + data.sizeY; j++)
                grid[j * 1000 + i]++;

    std::cout << std::count_if(grid.begin(), grid.end(), [](int const a) { return a > 1; }) << '\n';

    return 0;
}