#include <iostream>
#include <fstream>
#include <array>

bool light(int x, int y, const std::array<std::array<bool, 100>, 100> &current)
{
    int neighbours = 0;

    if (x > 0 && y > 0)
        neighbours += current[x - 1][y - 1];

    if (x > 0)
        neighbours += current[x - 1][y];

    if (x > 0 && y < 99)
        neighbours += current[x - 1][y + 1];

    if (y > 0)
        neighbours += current[x][y - 1];

    if (y < 99)
        neighbours += current[x][y + 1];

    if (x < 99 && y > 0)
        neighbours += current[x + 1][y - 1];

    if (x < 99)
        neighbours += current[x + 1][y];

    if (x < 99 && y < 99)
        neighbours += current[x + 1][y + 1];

    return current[x][y] ? neighbours == 2 || neighbours == 3 : neighbours == 3;
}

std::array<std::array<bool, 100>, 100> simulate(const std::array<std::array<bool, 100>, 100> &current)
{
    std::array<std::array<bool, 100>, 100> lights;

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            lights[i][j] = light(i, j, current);
        }
    }

    return lights;
}

int main()
{
    std::array<std::array<bool, 100>, 100> lights;

    {
        std::ifstream in("input");
        std::string line;

        for (int i = 0; i < 100; i++)
        {
            in >> line;

            for (int j = 0; j < 100; j++)
            {
                lights[i][j] = line[j] == '.' ? 0 : 1;
            }
        }
    }

    for (size_t i = 0; i < 100; i++)
    {
        lights = simulate(lights);
    }

    int count = 0;

    for (auto i : lights)
    {
        for (auto j : i)
        {
            count += j;
        }
    }

    std::cout << count << '\n';

    return 0;
}