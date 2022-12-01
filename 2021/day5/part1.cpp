#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

struct Line
{
    int x1, y1, x2, y2;

    bool is_straight()
    {
        return x1 == x2 || y1 == y2;
    }
};

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

        Line nums;
        stream >> nums.x1 >> nums.y1 >> nums.x2 >> nums.y2;

        if (nums.is_straight())
        {
            if (nums.x1 == nums.x2)
            {
                int min = std::min(nums.y1, nums.y2);
                int max = std::max(nums.y1, nums.y2);

                for (int y = min; y <= max; y++)
                {
                    points[nums.x1][y]++;
                }
            }
            else
            {
                int min = std::min(nums.x1, nums.x2);
                int max = std::max(nums.x1, nums.x2);

                for (int x = min; x <= max; x++)
                {
                    points[x][nums.y1]++;
                }
            }
        }
    }

    int count = 0;

    for (auto i : points) {
        for (auto j : i.second) {
            if (j.second >= 2) {
                count++;
            } 
        }
    }

    std::cout << count << '\n';

    return 0;
}