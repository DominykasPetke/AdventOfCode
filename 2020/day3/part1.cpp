#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("input");
    int sum = 0;
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

    int y = 0;

    for (long unsigned int x = 0; x < YEPTREE.size(); [&x, &y]() {
             x += 1;
             y += 3;
         }())
    {
        if (YEPTREE[x][y % YEPTREE[0].size()])
        {
            sum++;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}