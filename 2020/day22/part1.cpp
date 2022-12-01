#include <iostream>
#include <fstream>
#include <queue>

int main()
{
    std::string line;
    std::ifstream in("input");

    std::queue<int> player1;
    std::queue<int> player2;

    std::getline(in, line);
    int number;

    while (in >> number)
    {
        player1.push(number);
    }

    in.clear();
    std::getline(in, line);

    while (in >> number)
    {
        player2.push(number);
    }

    while (!player1.empty() && !player2.empty())
    {
        int p1 = player1.front();
        int p2 = player2.front();

        player1.pop();
        player2.pop();

        if (p1 > p2)
        {
            player1.push(p1);
            player1.push(p2);
        }
        else if (p1 < p2)
        {
            player2.push(p2);
            player2.push(p1);
        }
    }

    std::queue<int>* winner = player1.empty() ? &player2 : &player1;
    
    int sum = 0;

    while (winner->size() > 0)
    {
        sum += winner->front() * winner->size();
        winner->pop();
    }

    std::cout << sum << '\n';

    return 0;
}