#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>

int main()
{
    std::ifstream in("input");

    std::string line;
    std::array<int, 50 * 50> area;

    for (int j = 0; j < 50; j++)
    {
        in >> line;

        for (int i = 0; i < 50; i++)
            switch (line[i])
            {
            case '.':
                area[j * 50 + i] = 0;
                break;
            case '|':
                area[j * 50 + i] = 1;
                break;
            case '#':
                area[j * 50 + i] = 2;
            default:
                break;
            }
    }

    for (int i = 0; i < 10; i++)
    {
        std::array<int, 50 * 50> new_area = area;

        for (int x = 0; x < 50; x++)
            for (int y = 0; y < 50; y++)
            {
                std::array<int, 3> count;
                count.fill(0);

                if (x != 0 && y != 0)
                    count[area[(y - 1) * 50 + (x - 1)]]++;

                if (y != 0)
                    count[area[(y - 1) * 50 + x]]++;

                if (x != 0)
                    count[area[y * 50 + (x - 1)]]++;

                if (y != 49 && x != 0)
                    count[area[(y + 1) * 50 + (x - 1)]]++;

                if (y != 49)
                    count[area[(y + 1) * 50 + x]]++;

                if (x != 49)
                    count[area[y * 50 + (x + 1)]]++;

                if (y != 0 && x != 49)
                    count[area[(y - 1) * 50 + (x + 1)]]++;

                if (y != 49 && x != 49)
                    count[area[(y + 1) * 50 + (x + 1)]]++;

                if (area[y * 50 + x] == 0 && count[1] >= 3)
                {
                    new_area[y * 50 + x] = 1;
                    continue;
                }

                if (area[y * 50 + x] == 1 && count[2] >= 3)
                {
                    new_area[y * 50 + x] = 2;
                    continue;
                }

                if (area[y * 50 + x] == 2 && (count[2] < 1 || count[1] < 1))
                {
                    new_area[y * 50 + x] = 0;
                    continue;
                }
            }

        area = new_area;
    }

    std::cout << std::count(area.begin(), area.end(), 1) * std::count(area.begin(), area.end(), 2) << '\n';

    return 0;
}