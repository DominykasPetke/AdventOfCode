#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

int main()
{
    std::string line;
    std::ifstream in("input");

    std::map<int, std::map<int, int>> points;

    while (std::getline(in, line))
    {
        line.replace(line.find(","), 1, " ", 1);
        line.replace(line.find("->"), 2, " ", 1);
        line.replace(line.find(","), 1, " ", 1);

        std::stringstream stream(line);

        int x1, y1, x2, y2;
        stream >> x1 >> y1 >> x2 >> y2;

        if (x1 == x2)
        {
            int min = std::min(y1, y2);
            int max = std::max(y1, y2);

            for (int y = min; y <= max; y++)
            {
                points[x1][y]++;
            }
        }
        else if (y1 == y2)
        {
            int min = std::min(x1, x2);
            int max = std::max(x1, x2);

            for (int x = min; x <= max; x++)
            {
                points[x][y1]++;
            }
        }
        else
        {
            if (x2 < x1)
            {
                std::swap(x1, x2);
                std::swap(y1, y2);
            }

            if (y1 > y2)
            {
                for (int x = x1, y = y1; x <= x2 && y >= y2; x++, y--)
                {

                    points[x][y]++;
                }
            }
            else
            {
                for (int x = x1, y = y1; x <= x2 && y <= y2; x++, y++)
                {
                    points[x][y]++;
                }
            }
        }
    }

    int count = 0;

    for (auto i : points)
    {
        for (auto j : i.second)
        {
            if (j.second >= 2)
            {
                count++;
            }
        }
    }

    std::cout << count << '\n';

    return 0;
}