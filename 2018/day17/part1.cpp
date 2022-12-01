#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <functional>

enum
{
    sand = 0,
    clay = 1,
    flowing = 2,
    settled = 3,
    source = 4
};

int lowest_y = -1;
int highest_y = __INT_MAX__;

std::queue<std::function<void()>> func_queue;

void free_fall(int x, int y, std::map<int, std::map<int, int>> &map);
void left(int x, int y, std::map<int, std::map<int, int>> &map);
void right(int x, int y, std::map<int, std::map<int, int>> &map);

void fall_left(int x, int y, std::map<int, std::map<int, int>> &map)
{
    while (map[x + 1][y + 1] == clay && map[x][y + 1] != clay && map[x][y + 1] != settled)
    {
        y++;
        map[x][y] = flowing;
    }

    if (map[x][y + 1] == clay || map[x][y + 1] == settled)
        func_queue.push([x, y, &map]() { left(x, y, map); });
    else
        func_queue.push([x, y, &map]() { free_fall(x, y, map); });
}

void left(int x, int y, std::map<int, std::map<int, int>> &map)
{
    if (map[x][y] == settled)
        return;

    while (map[x - 1][y] != clay)
    {
        x--;
        map[x][y] = flowing;

        if (map[x][y + 1] == sand || map[x][y + 1] == flowing)
        {
            func_queue.push([x, y, &map]() { fall_left(x, y, map); });
            return;
        }
    }

    int startX = x;

    while (map[x + 1][y] == flowing)
        x++;

    if (map[x + 1][y] == clay)
        for (int i = startX; i <= x; i++)
        {
            map[i][y] = settled;

            if (map[i][y - 1] == flowing)
            {
                func_queue.push([i, y, &map]() { left(i, y - 1, map); });
                func_queue.push([i, y, &map]() { right(i, y - 1, map); });
            }
        }
}

void fall_right(int x, int y, std::map<int, std::map<int, int>> &map)
{
    while (map[x - 1][y + 1] == clay && map[x][y + 1] != clay && map[x][y + 1] != settled)
    {
        y++;
        map[x][y] = flowing;
    }

    if (map[x][y + 1] == clay || map[x][y + 1] == settled)
        func_queue.push([x, y, &map]() { right(x, y, map); });
    else
        func_queue.push([x, y, &map]() { free_fall(x, y, map); });
}

void right(int x, int y, std::map<int, std::map<int, int>> &map)
{
    if (map[x][y] == settled)
        return;

    while (map[x + 1][y] != clay)
    {
        x++;
        map[x][y] = flowing;

        if (map[x][y + 1] == sand || map[x][y + 1] == flowing)
        {
            func_queue.push([x, y, &map]() { fall_left(x, y, map); });
            return;
        }
    }

    int endX = x;

    while (map[x - 1][y] == flowing)
        x--;

    if (map[x - 1][y] == clay)
        for (int i = x; i <= endX; i++)
        {
            map[i][y] = settled;
            if (map[i][y - 1] == flowing)
            {
                func_queue.push([i, y, &map]() { left(i, y - 1, map); });
                func_queue.push([i, y, &map]() { right(i, y - 1, map); });
            }
        }
}

void free_fall(int x, int y, std::map<int, std::map<int, int>> &map)
{
    while (map[x][y + 1] != clay && map[x][y + 1] != settled)
    {
        y++;

        map[x][y] = flowing;

        if (y >= lowest_y)
            return;
    }

    func_queue.push([x, y, &map]() { left(x, y, map); });
    func_queue.push([x, y, &map]() { right(x, y, map); });
}

int main()
{
    std::ifstream in("input");

    std::map<int, std::map<int, int>> ground;

    std::string line;
    while (std::getline(in, line)) // input data
    {
        int x, y, end;
        if (line[0] == 'x')
        {
            line.erase(0, 2);
            x = std::stoi(line);

            line.erase(0, line.find('=') + 1);
            y = std::stoi(line);

            line.erase(0, line.find_last_of('.') + 1);
            end = std::stoi(line);

            if (end > lowest_y)
                lowest_y = end;

            if (y < highest_y)
                highest_y = y;

            for (int i = y; i <= end; i++)
                ground[x][i] = clay;
        }
        else if (line[0] == 'y')
        {
            line.erase(0, 2);
            y = std::stoi(line);

            line.erase(0, line.find('=') + 1);
            x = std::stoi(line);

            line.erase(0, line.find_last_of('.') + 1);
            end = std::stoi(line);

            if (y > lowest_y)
                lowest_y = y;

            if (y < highest_y)
                highest_y = y;

            for (int i = x; i <= end; i++)
                ground[i][y] = clay;
        }
    }

    ground[500][0] = source;

    func_queue.push([&ground]() { free_fall(500, 0, ground); });

    while (!func_queue.empty())
    {
        func_queue.front()();
        func_queue.pop();
    }

    int sum = 0;

    for (auto it = ground.begin(); it != ground.end(); it++) // sum all "water" blocks
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
            if (it2->first <= lowest_y && it2->first >= highest_y && it2->second > clay)
                sum++;

    std::cout << sum << '\n';

    return 0;
}