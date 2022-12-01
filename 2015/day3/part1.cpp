#include <iostream>
#include <fstream>
#include <set>

int main()
{
    std::ifstream in("input");
    std::string input;

    in >> input;

    std::set<std::pair<int, int>> visited;
    int x = 0, y = 0;

    visited.insert({x, y});

    for (auto i : input)
    {
        switch (i)
        {
        case '^':
            y++;
            break;
        case 'v':
            y--;
            break;
        case '<':
            x--;
            break;
        case '>':
            x++;
        default:
            break;
        }

        if (visited.count({x, y}) == 0) {
            visited.insert({x, y});
        }
    }

    std::cout << visited.size() << '\n';

    return 0;
}