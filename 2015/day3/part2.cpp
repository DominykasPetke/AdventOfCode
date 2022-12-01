#include <iostream>
#include <fstream>
#include <set>

int main()
{
    std::ifstream in("input");
    std::string input;

    in >> input;

    std::set<std::pair<int, int>> visited;
    int santaX = 0, santaY = 0, roboX = 0, roboY = 0;
    bool roboTurn = false;

    visited.insert({0, 0});

    for (auto i : input)
    {
        if (!roboTurn)
        {
            switch (i)
            {
            case '^':
                santaY++;
                break;
            case 'v':
                santaY--;
                break;
            case '<':
                santaX--;
                break;
            case '>':
                santaX++;
            default:
                break;
            }

            if (visited.count({santaX, santaY}) == 0)
            {
                visited.insert({santaX, santaY});
            }

            roboTurn = true;
        }
        else
        {
            switch (i)
            {
            case '^':
                roboY++;
                break;
            case 'v':
                roboY--;
                break;
            case '<':
                roboX--;
                break;
            case '>':
                roboX++;
            default:
                break;
            }

            if (visited.count({roboX, roboY}) == 0)
            {
                visited.insert({roboX, roboY});
            }

            roboTurn = false;
        }
    }

    std::cout << visited.size() << '\n';

    return 0;
}