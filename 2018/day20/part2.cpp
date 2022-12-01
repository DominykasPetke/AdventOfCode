#include <iostream>
#include <fstream>
#include <map>

struct Room
{
    unsigned int distance_from_start;

    Room()
        : distance_from_start(-1) {}

    bool operator<(Room const &other) const
    {
        return distance_from_start < other.distance_from_start;
    }
};

void read(std::size_t &i, std::string const regex, std::map<int, std::map<int, Room>> &map, int const start_x, int const start_y)
{
    int x = start_x;
    int y = start_y;
    for (; i < regex.size(); i++)
    {
        unsigned int dist = map[x][y].distance_from_start + 1;

        switch (regex[i])  // use char
        {
        case 'N':
            y--;

            if (dist < map[x][y].distance_from_start)
                map[x][y].distance_from_start = dist;

            break;
        case 'S':
            y++;

            if (dist < map[x][y].distance_from_start)
                map[x][y].distance_from_start = dist;

            break;
        case 'E':
            x++;

            if (dist < map[x][y].distance_from_start)
                map[x][y].distance_from_start = dist;

            break;
        case 'W':
            x--;

            if (dist < map[x][y].distance_from_start)
                map[x][y].distance_from_start = dist;

            break;
        case '|':
            x = start_x;
            y = start_y;
            break;
        case ')':
            return;
        case '(':
            i++;
            read(i, regex, map, x, y);
        default:
            break;
        }
    }
}

int main()
{
    std::string regex;

    {
        std::ifstream in("input");
        in >> regex;
    }

    regex.erase(0, 1);               // remove the unnecessary characters from the beginning
    regex.erase(regex.size() - 1);   // and the end 

    std::map<int, std::map<int, Room>> facility;  // storage

    int x = 0, y = 0;
    facility[0][0].distance_from_start = 0;

    std::size_t i = 0;
    read(i, regex, facility, x, y);   // interpret

    unsigned int count = 0;

    for (auto sec : facility)  // count up
        for (auto three : sec.second)
            if (three.second.distance_from_start >= 1000)
                count++;

    std::cout << count << '\n';

    return 0;
}