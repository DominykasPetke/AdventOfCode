#include <iostream>
#include <fstream>
#include <vector>
#include <array>

int main()
{
    std::ifstream in("input");
    std::string line;

    std::vector<std::vector<bool>> YEPTREE;

    while (std::getline(in, line))
    {
        std::vector<bool> row;

        for (char c : line)
        {
            switch (c)
            {
            case '#':
                row.push_back(1);
                break;
            case '.':
            default:
                row.push_back(0);
                break;
            }
        }

        YEPTREE.push_back(row);
    }

    std::array<std::pair<int, int>, 5> const moves = {{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}}};
    int64_t multiply = 1;

    for (auto i : moves)
    {

        int y = 0;
        int sum = 0;

        for (long unsigned int x = 0; x < YEPTREE.size(); [&x, &y, i]() {
                 x += i.second;
                 y += i.first;
             }())
        {
            if (YEPTREE[x][y % YEPTREE[0].size()])
            {
                sum++;
            }
        }

        multiply *= sum;
    }

    std::cout << multiply << '\n';

    return 0;
}