#include <fstream>
#include <iostream>

int index(int x, int y, int width)
{
    return (y - 1) * width + (x - 1);
}

int geologic_index(int x, int y, int t_x, int t_y, int depth, int *cache, int width)
{
    if (x == 0 && y == 0)
        return 0;

    if (x == t_x && y == t_y)
        return 0;

    if (y == 0)
        return x * 16807;

    if (x == 0)
        return y * 48271;

    if (cache[index(x, y, width)] > -1)
        return cache[index(x, y, width)];

    cache[index(x, y, width)] = ((geologic_index(x - 1, y, t_x, t_y, depth, cache, width) + depth) % 20183) *
                                ((geologic_index(x, y - 1, t_x, t_y, depth, cache, width) + depth) % 20183);

    return cache[index(x, y, width)];
}

int main()
{
    int depth, target_x, target_y;

    {
        std::ifstream in("input");

        std::string line;
        std::getline(in, line);

        line = line.substr(line.find(' ') + 1);
        depth = std::stoi(line);

        std::getline(in, line);
        line[line.find(',')] = ' ';

        line = line.substr(line.find(' ') + 1);
        target_x = std::stoi(line);

        line = line.substr(line.find(' ') + 1);
        target_y = std::stoi(line);
    }

    int width = target_x;
    int size = target_x * target_y;
    int *cache = new int[size];

    for (int i = 0; i < size; i++)
        cache[i] = -1;

    int sum = 0;

    for (int x = 0; x <= target_x; x++)
        for (int y = 0; y <= target_y; y++)
            sum += ((geologic_index(x, y, target_x, target_y, depth, cache, width) + depth) % 20183) % 3;

    std::cout << sum << '\n';

    return 0;
}