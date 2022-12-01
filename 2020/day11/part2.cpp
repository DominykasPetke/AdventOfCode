#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

enum State
{
    Floor = '.',
    Empty = 'L',
    Occupied = '#'
};

enum Direction
{
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left,
    TopLeft
};

bool ray(std::vector<std::string> const &positions, std::size_t i, std::size_t j, int direction)
{
    switch (direction)
    {
    case Direction::Top: // i-
        while (i > 0)
        {
            i--;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;
    case Direction::TopRight: // i-, j+
        while (i > 0 && j < positions[i].size() - 1)
        {
            i--;
            j++;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;

    case Direction::Right: // j+
        while (j < positions[i].size() - 1)
        {
            j++;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;

    case Direction::BottomRight: // i+, j+
        while (i < positions.size() - 1 && j < positions[i].size() - 1)
        {
            i++;
            j++;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;

    case Direction::Bottom: // i+
        while (i < positions.size() - 1)
        {
            i++;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;

    case Direction::BottomLeft: // i+ j-
        while (i < positions.size() - 1 && j > 0)
        {
            i++;
            j--;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;

    case Direction::Left:
        while (j > 0) // j-
        {
            j--;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;

    case Direction::TopLeft: // i-, j-
        while (i > 0 && j > 0)
        {
            i--;
            j--;

            switch (positions[i][j])
            {
            case State::Occupied:
                return true;
            case State::Empty:
                return false;
            default:
                break;
            }
        }

        return false;

    default:
        return false;
        break;
    }
}

uint count(std::vector<std::string> const &positions, std::size_t i, std::size_t j)
{
    uint ans = 0;

    for (int c = 0; c < 8; c++)
    {
        ans += ray(positions, i, j, c);
    }

    return ans;
}

int main()
{
    std::vector<std::string> positions;

    {
        std::string line;
        std::ifstream in("input");

        while (in >> line)
        {
            positions.push_back(line);
        }
    }

    bool changed = true;

    while (changed)
    {
        changed = false;
        std::vector<std::string> updated;

        for (std::size_t i = 0; i < positions.size(); i++)
        {
            std::string line = "";

            for (std::size_t j = 0; j < positions[i].size(); j++)
            {
                switch (positions[i][j])
                {
                case State::Empty:
                    line += count(positions, i, j) == 0 ? State::Occupied : State::Empty;
                    changed = changed || (line.back() != State::Empty);
                    break;
                case State::Occupied:
                    line += count(positions, i, j) < 5 ? State::Occupied : State::Empty;
                    changed = changed || (line.back() != State::Occupied);
                    break;
                case State::Floor:
                    line += State::Floor;
                default:
                    break;
                }
            }

            updated.push_back(line);
        }

        positions = updated;
    }

    int sum = 0;

    for (auto i : positions)
    {
        for (auto j : i)
        {
            if (j == State::Occupied)
            {
                sum++;
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}