#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::string input;
    {
        std::ifstream in("input");
        in >> input;
    }

    std::string scores = "37";

    long unsigned int first = 0;
    long unsigned int second = 1;

    auto search = scores.find(input);
    while (search == std::string::npos)
    {
        int sum = (scores[first] - '0') + (scores[second] - '0');

        if (sum >= 10)
        {
            scores.push_back(1 + '0');
            scores.push_back((sum % 10) + '0');
        }
        else
            scores.push_back(sum + '0');

        first += (scores[first] - '0') + 1;
        second += (scores[second] - '0') + 1;

        while (first >= scores.size())
            first = first - scores.size();

        while (second >= scores.size())
            second = second - scores.size();

        if (scores.size() >= input.size() + 2)
            search = scores.substr(scores.size() - input.size() - 2).find(input);
    }

    std::cout << scores.size() - input.size() - (2 - search) << '\n';

    return 0;
}