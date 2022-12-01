#include <iostream>
#include <fstream>
#include <unordered_map>

int main()
{
    std::string line;
    std::ifstream in("input");

    std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, bool>>>> space;

    int x = 0;

    while (std::getline(in, line)) // first part
    {
        for (std::size_t j = 0; j < line.size(); j++)
        {
            space[x][j][0][0] = line[j] == '#' ? 1 : 0;
        }

        x++;
    }

    int sspace_x_min = -1;
    int sspace_x_max = x;
    int sspace_y_min = -1;
    int sspace_y_max = line.size();
    int sspace_z_min = -1;
    int sspace_z_max = 2;
    int sspace_w_min = -1;
    int sspace_w_max = 2;

    for (int i = 0; i < 6; i++)
    {
        std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, std::unordered_map<int, bool>>>> new_space;

        bool min_x_write = 0;
        bool max_x_write = 0;
        bool min_y_write = 0;
        bool max_y_write = 0;
        bool min_z_write = 0;
        bool max_z_write = 0;
        bool min_w_write = 0;
        bool max_w_write = 0;

        for (x = sspace_x_min; x <= sspace_x_max; x++)
        {
            for (int y = sspace_y_min; y <= sspace_y_max; y++)
            {
                for (int z = sspace_z_min; z <= sspace_z_max; z++)
                {
                    for (int w = sspace_w_min; w <= sspace_w_max; w++)
                    {
                        int neighbours = [x, y, z, w, &space]() {
                            int sum = 0;

                            for (int i = x - 1; i <= x + 1; i++)
                            {
                                for (int j = y - 1; j <= y + 1; j++)
                                {
                                    for (int k = z - 1; k <= z + 1; k++)
                                    {
                                        for (int m = w - 1; m <= w + 1; m++)
                                        {
                                            sum += space[i][j][k][m];

                                            if (sum > 4)
                                            {
                                                return 4;
                                            }
                                        }
                                    }
                                }
                            }

                            return sum - space[x][y][z][w];
                        }();

                        if (space[x][y][z][w])
                        {
                            new_space[x][y][z][w] = (neighbours == 2 || neighbours == 3);
                        }
                        else
                        {
                            new_space[x][y][z][w] = (neighbours == 3);
                        }

                        if (new_space[x][y][z][w])
                        {
                            if (x == sspace_x_min)
                            {
                                min_x_write = 1;
                            }

                            if (y == sspace_y_min)
                            {
                                min_y_write = 1;
                            }

                            if (z == sspace_z_min)
                            {
                                min_z_write = 1;
                            }

                            if (w == sspace_w_min)
                            {
                                min_w_write = 1;
                            }

                            if (x == sspace_x_max - 1)
                            {
                                max_x_write = 1;
                            }

                            if (y == sspace_y_max - 1)
                            {
                                max_y_write = 1;
                            }

                            if (z == sspace_z_max - 1)
                            {
                                max_z_write = 1;
                            }

                            if (w == sspace_w_max - 1)
                            {
                                max_w_write = 1;
                            }
                        }
                    }
                }
            }
        }

        space = new_space;

        sspace_x_min -= min_x_write;
        sspace_x_max += max_x_write;
        sspace_y_min -= min_y_write;
        sspace_y_max += max_y_write;
        sspace_z_min -= min_z_write;
        sspace_z_max += max_z_write;
        sspace_w_min -= min_w_write;
        sspace_w_max += max_w_write;
    }

    int sum = 0;

    for (auto x : space)
    {
        for (auto y : x.second)
        {
            for (auto z : y.second)
            {
                for (auto w : z.second)
                {

                    sum += w.second;
                }
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}