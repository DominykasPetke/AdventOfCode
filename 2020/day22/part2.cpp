#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//false - 1 won, true - 2 won
bool play(std::vector<int> player1, std::vector<int> player2, std::vector<int> &winner)
{
    std::vector<std::pair<std::vector<int>, std::vector<int>>> memory;

    while (!player1.empty() && !player2.empty())
    {
        if (std::find_if(memory.begin(), memory.end(), [&player1, &player2](std::pair<std::vector<int>, std::vector<int>> &pair) {
                return player1 == pair.first && player2 == pair.second;
            }) != std::end(memory))
        {
            winner = player1;
            return false;
        }

        memory.push_back({player1, player2});

        std::size_t p1 = player1.front();
        std::size_t p2 = player2.front();

        player1.erase(player1.begin());
        player2.erase(player2.begin());

        if (p1 <= player1.size() && p2 <= player2.size())
        {
            std::vector<int> player1_recurse;

            for (std::size_t i = 0; i < p1; i++)
            {
                player1_recurse.push_back(player1[i]);
            }

            std::vector<int> player2_recurse;

            for (std::size_t i = 0; i < p2; i++)
            {
                player2_recurse.push_back(player2[i]);
            }

            if (play(player1_recurse, player2_recurse, winner))
            {
                player2.push_back(p2);
                player2.push_back(p1);
            }
            else
            {
                player1.push_back(p1);
                player1.push_back(p2);
            }
        }
        else
        {
            if (p1 > p2)
            {
                player1.push_back(p1);
                player1.push_back(p2);
            }
            else if (p1 < p2)
            {
                player2.push_back(p2);
                player2.push_back(p1);
            }
        }
    }

    if (player1.empty())
    {
        winner = player2;
        return true;
    }
    else
    {
        winner = player1;
        return false;
    }
}

int main()
{
    std::string line;
    std::ifstream in("input");

    std::vector<int> player1;
    std::vector<int> player2;

    std::getline(in, line);
    int number;

    while (in >> number)
    {
        player1.push_back(number);
    }

    in.clear();
    std::getline(in, line);

    while (in >> number)
    {
        player2.push_back(number);
    }

    std::vector<int> winner;
    play(player1, player2, winner);

    int sum = 0;

    while (winner.size() > 0)
    {
        sum += winner.front() * winner.size();
        winner.erase(winner.begin());
    }

    std::cout << sum << '\n';

    return 0;
}