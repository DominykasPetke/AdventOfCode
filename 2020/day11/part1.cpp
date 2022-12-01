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

uint count(std::vector<std::string> const &positions, std::size_t i, std::size_t j)
{
    uint ans = 0;

    if (i > 0)
    {
        if (j > 0 && positions[i - 1][j - 1] == State::Occupied)
        {
            ans++;
        }

        if (j < positions[i].size() - 1 && positions[i - 1][j + 1] == State::Occupied)
        {
            ans++;
        }

        if (positions[i - 1][j] == State::Occupied)
        {
            ans++;
        }
    }

    if (i < positions.size() - 1)
    {
        if (j > 0 && positions[i + 1][j - 1] == State::Occupied)
        {
            ans++;
        }

        if (j < positions[i].size() - 1 && positions[i + 1][j + 1] == State::Occupied)
        {
            ans++;
        }

        if (positions[i + 1][j] == State::Occupied)
        {
            ans++;
        }
    }

    if (j > 0 && positions[i][j - 1] == State::Occupied)
    {
        ans++;
    }

    if (j < positions[i].size() - 1 && positions[i][j + 1] == State::Occupied)
    {
        ans++;
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
                    line += count(positions, i, j) < 4 ? State::Occupied : State::Empty;
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