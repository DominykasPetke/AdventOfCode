#include <iostream>
#include <fstream>
#include <unordered_map> // I am speed
#include <algorithm>

int main()
{
    std::string line;
    std::ifstream in("input");

    std::unordered_map<int, std::unordered_map<int, bool>> tiles; // 1 = black, 0 = white
    int sum = 0;

    while (std::getline(in, line))
    {
        short dir = 0;
        int pos_x = 0;
        int pos_y = 0;

        for (const char c : line)
        {
            switch (c)
            {
            case 'e':
                pos_y += dir == 0 ? 2 : 1;
                pos_x += dir;
                dir = 0;
                break;
            case 'n':
                dir = 1;
                break;
            case 's':
                dir = -1;
                break;
            case 'w':
                pos_y += dir == 0 ? -2 : -1;
                pos_x += dir;
                dir = 0;
                break;

            default:
                break;
            }
        }

        tiles[pos_x][pos_y] = !tiles[pos_x][pos_y];

        sum += tiles[pos_x][pos_y] ? 1 : -1;
    }

    std::cout << "Part 1: " << sum << '\n';

    for (int i = 0; i < 100; i++)
    {
        std::unordered_map<int, std::unordered_map<int, bool>> new_tiles; // 1 = black, 0 = white

        const auto x_func = [](std::pair<int, std::unordered_map<int, bool>> const &t, std::pair<int, std::unordered_map<int, bool>> const &f) {
            return t.first < f.first;
        };

        const int start_x = std::min_element(tiles.begin(), tiles.end(), x_func)->first - 1;
        const int end_x = std::max_element(tiles.begin(), tiles.end(), x_func)->first + 1;

        const auto y_func = [](std::pair<int, bool> const &t, std::pair<int, bool> const &f) {
            return t.first < f.first;
        };

        const auto start_y_search = std::min_element(tiles.begin(),
                                                     tiles.end(),
                                                     [&y_func](std::pair<int, std::unordered_map<int, bool>> const &t, std::pair<int, std::unordered_map<int, bool>> const &f) {
                                                         return std::min_element(t.second.begin(), t.second.end(), y_func)->first < std::min_element(f.second.begin(), f.second.end(), y_func)->first;
                                                     });

        const int start_y = std::min_element(start_y_search->second.begin(), start_y_search->second.end(), y_func)->first - 1;

        const auto end_y_search = std::max_element(tiles.begin(),
                                                   tiles.end(),
                                                   [&y_func](std::pair<int, std::unordered_map<int, bool>> const &t, std::pair<int, std::unordered_map<int, bool>> const &f) {
                                                       return std::max_element(t.second.begin(), t.second.end(), y_func)->first < std::max_element(f.second.begin(), f.second.end(), y_func)->first;
                                                   });

        const int end_y = std::max_element(end_y_search->second.begin(), end_y_search->second.end(), y_func)->first + 1;

        for (int x = start_x; x <= end_x; x++)
        {
            for (int y = start_y - ((start_y % 2 == 0) != (x % 2 == 0)); y <= end_y + ((end_y % 2 == 0) != (x % 2 == 0)); y += 2)
            {
                const u_short neighbours = tiles[x][y + 2] +
                                           tiles[x][y - 2] +
                                           tiles[x + 1][y + 1] +
                                           tiles[x + 1][y - 1] +
                                           tiles[x - 1][y + 1] +
                                           tiles[x - 1][y - 1];

                if (tiles[x][y])
                {
                    if (neighbours == 1 || neighbours == 2)
                    {
                        new_tiles[x][y] = 1;
                    }
                    else
                    {
                        sum--;
                    }
                }
                else if (neighbours == 2)
                {
                    new_tiles[x][y] = 1;
                    sum++;
                }
            }
        }

        tiles = new_tiles;
    }

    std::cout << "Part 2: " << sum << '\n';

    return 0;
}