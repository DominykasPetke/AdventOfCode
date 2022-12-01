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
    int max_amount = 1;  // id count

    std::array<std::pair<int, int>, LINE_SIZE * LINE_SIZE> grid;
    grid.fill({0, 0}); // all data be 0 in start

    { // input data
        char temp;

        while (in >> x >> temp >> y)
        {
            grid[y * LINE_SIZE + x] = {max_amount, 0};

            max_amount++;
        }
    }

    int i = 0; // counter

    for (; i < LINE_SIZE; i++) // make edges special, cuz bounds checking is annoying and it doesn't really matter here
    {
        grid[i * LINE_SIZE] = {-1, -1};
        grid[i] = {-1, -1};
        grid[LINE_SIZE * (LINE_SIZE - 1) + i] = {-1, -1};
        grid[i * LINE_SIZE + (LINE_SIZE - 1)] = {-1, -1};
    }

    i = 0; // distance from parent

    //while non-0 data is there
    while (std::any_of(grid.begin(), grid.end(), [](std::pair<int, int> const &a) {
        return a.first == 0;
    }))
    {
        std::vector<std::pair<int, int>> locations;

        //make an index of locations to add data around
        for (x = 1; x < LINE_SIZE - 1; x++)
            for (y = 1; y < LINE_SIZE - 1; y++)
                if (int curr = y * LINE_SIZE + x; grid[curr].first > 0 && grid[curr].second == i)
                    locations.push_back({x, y});

        i++; // increment distance from parent here

        //make data around locations
        for (auto j : locations)
        {
            x = j.first;
            y = j.second;
            int curr = y * LINE_SIZE + x;

            if (int pos = (y - 1) * LINE_SIZE + x; grid[pos].first == 0 || grid[pos].first == -1) // if region not taken
                grid[pos] = {grid[curr].first, i};
            else if (grid[pos].first != grid[curr].first && grid[pos].second == i) // else if distance to other parent is equal
                grid[pos] = {-2, -2};

            if (int pos = (y + 1) * LINE_SIZE + x; grid[pos].first == 0 || grid[pos].first == -1) // two side
                grid[pos] = {grid[curr].first, i};
            else if (grid[pos].first != grid[curr].first && grid[pos].second == i)
                grid[pos] = {-2, -2};

            if (int pos = y * LINE_SIZE + (x + 1); grid[pos].first == 0 || grid[pos].first == -1) // three side
                grid[pos] = {grid[curr].first, i};
            else if (grid[pos].first != grid[curr].first && grid[pos].second == i)
                grid[pos] = {-2, -2};

            if (int pos = y * LINE_SIZE + (x - 1); grid[pos].first == 0 || grid[pos].first == -1) // four side
                grid[pos] = {grid[curr].first, i};
            else if (grid[pos].first != grid[curr].first && grid[pos].second == i)
                grid[pos] = {-2, -2};
        }
    }

    std::vector<int> infinites;
    // exclude infinite area IDs
    for (i = 0; i < LINE_SIZE; i++)
    {
        infinites.push_back(grid[i * LINE_SIZE].first);
        infinites.push_back(grid[i].first);
        infinites.push_back(grid[LINE_SIZE * (LINE_SIZE - 1) + i].first);
        infinites.push_back(grid[i * LINE_SIZE + (LINE_SIZE - 1)].first);
    }

    std::sort(infinites.begin(), infinites.end());                                     // sort the infinites
    infinites.erase(std::unique(infinites.begin(), infinites.end()), infinites.end()); // and remove dupes
    infinites.erase(infinites.begin(), infinites.begin() + 1);                         // and remove -1

    std::vector<std::pair<int, int>> sums;

    for (i = 1; i < max_amount; i++) // get all non-infinite sums
        if (std::count(infinites.begin(), infinites.end(), i) != 1) // skip infinites
            sums.push_back({i, std::count_if(grid.begin(), grid.end(), [i](std::pair<int, int> const &a) { return a.first == i; })});

    std::nth_element(sums.begin(), sums.begin(), sums.end(), [](std::pair<int, int> const &t, std::pair<int, int> const &f) { return t.second > f.second; }); // sort to the first element only

    std::cout << sums[0].second << '\n'; // print answer

    return 0;
}