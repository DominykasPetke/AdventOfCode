#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>

struct coords
{
    int x, y, sizeX, sizeY, ID;
};

bool read(std::ifstream &in, coords &out)
{
    std::string line;

    while (std::getline(in, line))
    {
        line = line.erase(0, 1);
        out.ID = std::stoi(line);
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

    std::vector<coords> data;
    coords temp;
    while (read(in, temp))
    {
        for (int i = temp.x; i < temp.x + temp.sizeX; i++)
            for (int j = temp.y; j < temp.y + temp.sizeY; j++)
                grid[j * 1000 + i]++;

        data.push_back(temp);
    }

    std::cout << data[std::find_if(data.begin(), data.end(), [&grid](coords const &a) {
                          for (int i = a.x; i < a.x + a.sizeX; i++)
                              for (int j = a.y; j < a.y + a.sizeY; j++)
                                  if (grid[j * 1000 + i] != 1)
                                      return false;
                          return true;
                      }) -
                      data.begin()]
                     .ID
              << '\n';

    return 0;
}