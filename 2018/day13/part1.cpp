#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Cart
{
    int X, Y;
    int next_turn;
    int direction;

    Cart(int newX, int newY, int newDirection)
        : X(newX), Y(newY), next_turn(0), direction(newDirection) {}

    bool operator<(Cart const other) const
    {
        if (X < other.X)
            return true;
        if (X > other.X)
            return false;
        if (Y < other.Y)
            return true;
        return false;
    }

    bool operator==(Cart const other) const
    {
        return X == other.X && Y == other.Y;
    }
};

int main()
{
    std::ifstream in("input");

    std::vector<Cart> carts;
    std::vector<std::string> map;
    std::string line;

    while (std::getline(in, line))
    {
        auto loc = line.find('<');
        while (loc != std::string::npos)
        {
            carts.push_back({(int)map.size(), (int)loc, 3});
            line[loc] = '-';
            loc = line.find('<');
        }

        loc = line.find('>');
        while (loc != std::string::npos)
        {
            carts.push_back({(int)map.size(), (int)loc, 1});
            line[loc] = '-';
            loc = line.find('>');
        }

        loc = line.find('^');
        while (loc != std::string::npos)
        {
            carts.push_back({(int)map.size(), (int)loc, 0});
            line[loc] = '|';
            loc = line.find('^');
        }

        loc = line.find('v');
        while (loc != std::string::npos)
        {
            carts.push_back({(int)map.size(), (int)loc, 2});
            line[loc] = '|';
            loc = line.find('v');
        }

        map.push_back(line);
    }

    while (1)
    {
        std::sort(carts.begin(), carts.end());

        for (auto &i : carts)
        {
            switch (i.direction)
            {
            case 0:
                i.X--;
                switch (map[i.X][i.Y])
                {
                case '\\':
                    i.direction = 3;
                    break;

                case '/':
                    i.direction = 1;
                    break;

                case '+':
                    switch (i.next_turn)
                    {
                    case 2:
                        i.direction = 1;
                        i.next_turn = 0;
                        break;

                    case 0:
                        i.direction = 3;
                    case 1:
                        i.next_turn++;
                    default:
                        break;
                    }

                case '|':
                default:
                    break;
                }
                break;

            case 1:
                i.Y++;
                switch (map[i.X][i.Y])
                {
                case '\\':
                    i.direction = 2;
                    break;

                case '/':
                    i.direction = 0;
                    break;

                case '+':
                    switch (i.next_turn)
                    {
                    case 2:
                        i.direction = 2;
                        i.next_turn = 0;
                        break;

                    case 0:
                        i.direction = 0;
                    case 1:
                        i.next_turn++;
                    default:
                        break;
                    }

                case '-':
                default:
                    break;
                }
                break;

            case 2:
                i.X++;
                switch (map[i.X][i.Y])
                {
                case '\\':
                    i.direction = 1;
                    break;

                case '/':
                    i.direction = 3;
                    break;

                case '+':
                    switch (i.next_turn)
                    {
                    case 2:
                        i.direction = 3;
                        i.next_turn = 0;
                        break;

                    case 0:
                        i.direction = 1;
                    case 1:
                        i.next_turn++;
                    default:
                        break;
                    }

                case '-':
                default:
                    break;
                }
                break;
                
            case 3:
                i.Y--;
                switch (map[i.X][i.Y])
                {
                case '\\':
                    i.direction = 0;
                    break;

                case '/':
                    i.direction = 2;
                    break;

                case '+':
                    switch (i.next_turn)
                    {
                    case 2:
                        i.direction = 0;
                        i.next_turn = 0;
                        break;

                    case 0:
                        i.direction = 2;
                    case 1:
                        i.next_turn++;
                    default:
                        break;
                    }

                case '-':
                default:
                    break;
                }

            default:
                break;
            }

            if (std::count_if(carts.cbegin(), carts.cend(), [i](Cart const &a) { return a == i; }) > 1)
            {
                std::cout << i.Y << ',' << i.X << '\n'; // I realised I mixed up the axis
                return 0;
            }
        }
    }

    return 0;
}