#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <vector>

#define LINE_SIZE 500

int main()
{
    std::ifstream in("input");

    int x, y;

    std::vector<std::pair<int, int>> coords;

    { // input data
        char temp;

        while (in >> x >> temp >> y)
            coords.push_back({x, y});
    }

    std::array<int, LINE_SIZE * LINE_SIZE> grid;
    grid.fill(0); // all data be 0 in start

    for (x = 0; x < LINE_SIZE; x++)
        for (y = 0; y < LINE_SIZE; y++)
            grid[y * LINE_SIZE + x] = [&coords, x, y]() {
                int sum = 0;

                for (auto i : coords)
                {
                    sum += std::abs(i.first - x);
                    sum += std::abs(i.second - y);
                }

                return sum;
            }();

    std::cout << std::count_if(grid.begin(), grid.end(), [](int const a){ return a < 10000; }) << '\n';

    return 0;
}