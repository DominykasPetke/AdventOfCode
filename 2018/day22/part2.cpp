#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

struct MinusOne
{
    int data;

    MinusOne() : data(-1) {}
};

enum
{
    torch,
    climbing_gear,
    nothing
};

enum
{
    rocky,
    wet,
    narrow
};

struct Location
{
    int x, y;
    int time;
    int tool;

    Location() {}

    Location(int new_x, int new_y, int new_time, int new_tool)
        : x(new_x), y(new_y), time(new_time), tool(new_tool) {}

    bool operator<(Location const &other) const
    {
        return time < other.time;
    }
};

class Queue
{
    std::vector<Location> data;

  public:
    Location top()
    {
        std::sort(data.begin(), data.end());

        return data.front();
    }

    bool empty()
    {
        return data.empty();
    }

    void push(Location const &loc)
    {
        if (auto search = std::find_if(data.begin(), data.end(), [loc](Location const &vec) {
                return vec.x == loc.x && vec.y == loc.y && vec.tool == loc.tool;
            });
            search != data.end())
        {
            if (search->time > loc.time)
            {
                search->time = loc.time;
            }
        }
        else
        {
            data.push_back(loc);
        }
    }

    void pop()
    {
        data.erase(data.begin(), data.begin() + 1);
    }

    std::size_t size()
    {
        return data.size();
    }
};

int geologic_index(int x,
                   int y,
                   int t_x,
                   int t_y,
                   int depth,
                   std::map<int, std::map<int, MinusOne>> &cache)
{
    if (x == 0 && y == 0)
        return 0;

    if (x == t_x && y == t_y)
        return 0;

    if (y == 0)
        return x * 16807;

    if (x == 0)
        return y * 48271;

    if (cache[x][y].data > -1)
        return cache[x][y].data;

    cache[x][y].data = ((geologic_index(x - 1, y, t_x, t_y, depth, cache) + depth) % 20183) *
                       ((geologic_index(x, y - 1, t_x, t_y, depth, cache) + depth) % 20183);

    return cache[x][y].data;
}

int area_type(int x,
              int y,
              int t_x,
              int t_y,
              int depth,
              std::map<int, std::map<int, MinusOne>> &cache)
{
    return ((geologic_index(x, y, t_x, t_y, depth, cache) + depth) % 20183) % 3;
}

void add(Queue &q, Location loc, int current, int other)
{
    switch (current)
    {
    case rocky:
        switch (loc.tool)
        {
        case climbing_gear:
            if (other == wet)
                q.push({loc.x, loc.y, loc.time + 1, loc.tool});
            else
                q.push({loc.x, loc.y, loc.time + 8, torch});
            break;
        case torch:
            if (other == narrow)
                q.push({loc.x, loc.y, loc.time + 1, loc.tool});
            else
                q.push({loc.x, loc.y, loc.time + 8, climbing_gear});
            break;
        default:
            break;
        }
        break;
    case wet:
        switch (loc.tool)
        {
        case climbing_gear:
            if (other == rocky)
                q.push({loc.x, loc.y, loc.time + 1, loc.tool});
            else
                q.push({loc.x, loc.y, loc.time + 8, nothing});
            break;
        case nothing:
            if (other == narrow)
                q.push({loc.x, loc.y, loc.time + 1, loc.tool});
            else
                q.push({loc.x, loc.y, loc.time + 8, climbing_gear});
            break;
        default:
            break;
        }
        break;

    case narrow:
        switch (loc.tool)
        {
        case nothing:
            if (other == wet)
                q.push({loc.x, loc.y, loc.time + 1, loc.tool});
            else
                q.push({loc.x, loc.y, loc.time + 8, torch});
            break;
        case torch:
            if (other == rocky)
                q.push({loc.x, loc.y, loc.time + 1, loc.tool});
            else
                q.push({loc.x, loc.y, loc.time + 8, nothing});
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void queue_add(Queue &q,
               std::map<int, std::map<int, std::map<int, MinusOne>>> &dists,
               Location loc,
               int depth,
               int t_x,
               int t_y,
               std::map<int, std::map<int, MinusOne>> &cache)
{
    int current = area_type(loc.x, loc.y, t_x, t_y, depth, cache);
    if (dists[loc.x + 1][loc.y][loc.tool].data < 0 || dists[loc.x + 1][loc.y][loc.tool].data > loc.time) // right
    {
        if (int other = area_type(loc.x + 1, loc.y, t_x, t_y, depth, cache);
            current != other)
        {
            add(q, {loc.x + 1, loc.y, loc.time, loc.tool}, current, other);
        }
        else
        {
            q.push({loc.x + 1, loc.y, loc.time + 1, loc.tool});
        }
    }

    if (dists[loc.x][loc.y + 1][loc.tool].data < 0 || dists[loc.x][loc.y + 1][loc.tool].data > loc.time) // down
    {
        if (int other = area_type(loc.x, loc.y + 1, t_x, t_y, depth, cache);
            current != other)
        {
            add(q, {loc.x, loc.y + 1, loc.time, loc.tool}, current, other);
        }
        else
        {
            q.push({loc.x, loc.y + 1, loc.time + 1, loc.tool});
        }
    }

    if (loc.x > 0 && (dists[loc.x - 1][loc.y][loc.tool].data < 0 || dists[loc.x - 1][loc.y][loc.tool].data > loc.time)) // left
    {
        if (int other = area_type(loc.x - 1, loc.y, t_x, t_y, depth, cache);
            current != other)
        {
            add(q, {loc.x - 1, loc.y, loc.time, loc.tool}, current, other);
        }
        else
        {
            q.push({loc.x - 1, loc.y, loc.time + 1, loc.tool});
        }
    }

    if (loc.y > 0 && (dists[loc.x][loc.y - 1][loc.tool].data < 0 || dists[loc.x][loc.y - 1][loc.tool].data > loc.time)) // up
    {
        if (int other = area_type(loc.x, loc.y - 1, t_x, t_y, depth, cache);
            current != other)
        {
            add(q, {loc.x, loc.y - 1, loc.time, loc.tool}, current, other);
        }
        else
        {
            q.push({loc.x, loc.y - 1, loc.time + 1, loc.tool});
        }
    }
}

int main()
{
    int depth, target_x, target_y;

    { // input
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

    std::map<int, std::map<int, MinusOne>> cache;
    std::map<int, std::map<int, std::map<int, MinusOne>>> distances;

    Queue queue;

    queue_add(queue, distances, {0, 0, 0, torch}, depth, target_x, target_y, cache);
    distances[0][0][torch].data = 0;

    while (!queue.empty())
    {
        Location top = queue.top();

        distances[top.x][top.y][top.tool].data = top.time;

        // std::cout << queue.size() << " in queue. Top element: {" << top.x << ", " << top.y << ", " << top.time << ", " <<
        //     [top]() {std::array<std::string, 3> a = {"torch", "climbing gear", "nothing"}; return a[top.tool]; }()
        //           << "} Surface: " <<
        //           [top, target_x, target_y, depth, &cache]() {
        //               std::array<std::string, 3> a = {"rocky", "wet", "narrow"};
        //                return a[area_type(top.x, top.y, target_x, target_y, depth, cache)];
        //                }() << '\n';

        if (top.x == target_x && top.y == target_y) // win
        {
            if (top.tool != torch)
                queue.push({top.x, top.y, top.time + 7, torch});
            else
            {
                std::cout << top.time << std::endl;
                return 0;
            }
        }

        queue_add(queue, distances, top, depth, target_x, target_y, cache);

        queue.pop();
    }

    return 0;
}