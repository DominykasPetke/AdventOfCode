#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

struct Unit
{
    std::size_t x, y;
    int attack_strength;
    int health_points;
    bool is_goblin;

    Unit(std::size_t new_X, std::size_t new_Y, bool goblin)
        : x(new_X), y(new_Y), attack_strength(3), health_points(200), is_goblin(goblin) {}

    bool operator<(Unit const &other) const
    {
        if (y < other.y)
            return true;
        if (y > other.y)
            return false;
        if (x < other.x)
            return true;
        return false;
    }

    bool operator==(Unit const &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct Coords
{
    std::size_t x, y;

    Coords(std::size_t new_x, std::size_t new_y)
        : x(new_x), y(new_y) {}

    bool operator<(Coords const &other) const
    {
        if (y < other.y)
            return true;
        if (y > other.y)
            return false;
        if (x < other.x)
            return true;
        return false;
    }

    bool operator==(Coords const &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(Coords const &other) const
    {
        return x != other.x || y != other.y;
    }
};

bool is_wall(Coords const &c,
             std::vector<std::string> const &map)
{
    return map[c.y][c.x] == '#';
}

bool is_unit(Coords const &c,
             std::vector<Unit> const &units)
{
    return std::find_if(units.begin(), units.end(), [c](Unit const &a) {
               return a.health_points > 0 && a.x == c.x && a.y == c.y;
           }) != units.end();
}

void find_in_range(std::vector<int> &in_range,
                   std::vector<Unit> const &units,
                   std::vector<int> const &targets,
                   std::size_t orig_x,
                   std::size_t orig_y)
{
    std::size_t x = orig_x;
    std::size_t y = orig_y + 1;
    //find units in range
    if (auto search = std::find_if(targets.begin(), targets.end(), [x, y, &units](int const a) {
            return units[a].x == x && units[a].y == y && units[a].health_points > 0;
        });
        search != targets.end())
        in_range.push_back(*search);

    y = orig_y - 1;
    //find units in range
    if (auto search = std::find_if(targets.begin(), targets.end(), [x, y, &units](int const a) {
            return units[a].x == x && units[a].y == y && units[a].health_points > 0;
        });
        search != targets.end())
        in_range.push_back(*search);

    x = orig_x + 1;
    y = orig_y;
    //find units in range
    if (auto search = std::find_if(targets.begin(), targets.end(), [x, y, &units](int const a) {
            return units[a].x == x && units[a].y == y && units[a].health_points > 0;
        });
        search != targets.end())
        in_range.push_back(*search);

    x = orig_x - 1;
    //find units in range
    if (auto search = std::find_if(targets.begin(), targets.end(), [x, y, &units](int const a) {
            return units[a].x == x && units[a].y == y && units[a].health_points > 0;
        });
        search != targets.end())

        in_range.push_back(*search);
}

std::vector<Coords> find_adjacent(std::vector<int> const &targets,
                                  std::vector<Unit> const &units,
                                  std::vector<std::string> const &map)
{
    std::vector<Coords> range;

    for (auto ranges : targets) // find adjacent free squares next to the targets
    {
        Coords loc = {units[ranges].x, units[ranges].y - 1};

        //  check if spot is free
        if (!is_wall(loc, map) && !is_unit(loc, units))
            range.push_back(loc);

        loc.y = units[ranges].y + 1;
        //  check if spot is free
        if (!is_wall(loc, map) && !is_unit(loc, units))
            range.push_back(loc);

        loc.y = units[ranges].y;
        loc.x = units[ranges].x - 1;
        //  check if spot is free
        if (!is_wall(loc, map) && !is_unit(loc, units))
            range.push_back(loc);

        loc.x = units[ranges].x + 1;
        //  check if spot is free
        if (!is_wall(loc, map) && !is_unit(loc, units))
            range.push_back(loc);
    }

    std::sort(range.begin(), range.end());
    return range;
}

void add_to_queue(std::queue<std::pair<Coords, int>> &queue,
                  std::vector<std::string> const &map,
                  std::vector<Unit> const &units,
                  std::map<Coords, int> &distances,
                  Coords const &orig_loc,
                  int const distance)
{
    Coords loc = {orig_loc.x, orig_loc.y - 1};
    // check if square is empty
    if ((distances[loc] == 0 || distances[loc] > distance) && !is_wall(loc, map) && !is_unit(loc, units))
    {
        queue.push({loc, distance});
        distances[loc] = distance;
    }

    loc.y = orig_loc.y + 1;
    // check if square is empty
    if ((distances[loc] == 0 || distances[loc] > distance) && !is_wall(loc, map) && !is_unit(loc, units))
    {
        queue.push({loc, distance});
        distances[loc] = distance;
    }

    loc.x = orig_loc.x - 1;
    loc.y = orig_loc.y;
    // check if square is empty
    if ((distances[loc] == 0 || distances[loc] > distance) && !is_wall(loc, map) && !is_unit(loc, units))
    {
        queue.push({loc, distance});
        distances[loc] = distance;
    }

    loc.x = orig_loc.x + 1;
    // check if square is empty
    if ((distances[loc] == 0 || distances[loc] > distance) && !is_wall(loc, map) && !is_unit(loc, units))
    {
        queue.push({loc, distance});
        distances[loc] = distance;
    }
}

Coords find_closest(std::vector<Coords> const &range,
                    Coords const &unit,
                    std::vector<Unit> const &units,
                    std::vector<std::string> const &map)

{
    std::map<Coords, int> distances;
    std::queue<std::pair<Coords, int>> queue;

    add_to_queue(queue, map, units, distances, {unit.x, unit.y}, 1);

    while (!queue.empty()) // while still something to check
    {
        std::pair<Coords, int> loc = queue.front();
        queue.pop();

        add_to_queue(queue, map, units, distances, loc.first, loc.second + 1);
    }

    std::vector<std::pair<Coords, int>> reachable;

    for (auto pos : range) // find all reachable ranges
        if (distances[pos] > 0)
            reachable.push_back({pos, distances[pos]});

    if (reachable.size() > 0)
    {
        std::stable_sort(reachable.begin(), reachable.end(), [](std::pair<Coords, int> const &t, std::pair<Coords, int> const &f) { return t.second < f.second; });
        return reachable[0].first;
    }
    else
        return {0, 0};
}

int main()
{
    std::vector<std::string> map;
    std::ifstream in("input");
    std::string line;

    std::vector<Unit> units;

    while (std::getline(in, line)) // input map and starting unit positions
    {
        auto search = line.find('E');
        while (search != std::string::npos)
        {
            units.push_back({search, map.size(), false});
            line[search] = '.';
            search = line.find('E');
        }

        search = line.find('G');
        while (search != std::string::npos)
        {
            units.push_back({search, map.size(), true});
            line[search] = '.';
            search = line.find('G');
        }

        map.push_back(line);
    }

    int current_turn = 0;
    while (1)
    {
        std::sort(units.begin(), units.end()); // sort the units to determine movement order

        for (auto &unit : units) // make each unit's turn
            if (unit.health_points > 0)
            {
                std::vector<int> targets;

                for (auto i = units.begin(); i < units.end(); i++) // find targets (a.k.a. enemies)
                    if (i->is_goblin != unit.is_goblin && i->health_points > 0)
                        targets.push_back(i - units.begin());

                if (targets.size() == 0) // if no targets end the game
                {
                    int sum = 0;

                    for (auto d : units) // sum the health of all remaining alive units
                        if (d.health_points > 0)
                            sum += d.health_points;

                    std::cout << current_turn * sum << '\n'; // output
                    return 0;                                // and finish
                }

                std::vector<int> in_range;

                find_in_range(in_range, units, targets, unit.x, unit.y);

                if (in_range.size() == 0)
                {
                    std::vector<Coords> range = find_adjacent(targets, units, map);

                    if (range.size() > 0)
                    {
                        Coords move_toward = find_closest(range, {unit.x, unit.y}, units, map);

                        if (move_toward.x != 0 && move_toward.y != 0)
                            if ((move_toward.x == unit.x && move_toward.y + 1 == unit.y) ||
                                (move_toward.x == unit.x && move_toward.y - 1 == unit.y) ||
                                (move_toward.x + 1 == unit.x && move_toward.y == unit.y) ||
                                (move_toward.x - 1 == unit.x && move_toward.y == unit.y))
                            {
                                unit.x = move_toward.x;
                                unit.y = move_toward.y;
                            }
                            else
                            {
                                std::vector<Coords> stuff = find_adjacent({0}, {unit}, map);

                                Coords new_loc = find_closest(stuff, move_toward, units, map);

                                unit.x = new_loc.x;
                                unit.y = new_loc.y;
                            }
                        else
                            continue;

                        find_in_range(in_range, units, targets, unit.x, unit.y);
                    }
                }

                if (in_range.size() > 0)
                {
                    std::sort(in_range.begin(), in_range.end(), [units](int const t, int const f) {
                        if (units[t].health_points < units[f].health_points)
                            return true;
                        if (units[t].health_points > units[f].health_points)
                            return false;
                        Coords tr = {units[t].x, units[t].y};
                        Coords fa = {units[f].x, units[f].y};

                        return tr < fa;
                    });

                    units[in_range[0]].health_points -= unit.attack_strength;
                }
            }

        for (auto it = units.begin(); it != units.end();)
            if (it->health_points < 0)
                it = units.erase(it);
            else
                ++it;

        current_turn++;
    }

    return 0;
}