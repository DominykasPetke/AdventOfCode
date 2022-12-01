#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    long unsigned int input;
    {
        std::ifstream in("input");
        in >> input;
    }

    std::vector<int> scores = {3, 7};

    long unsigned int first = 0;
    long unsigned int second = 1;

    while (scores.size() < input + 11)
    {
        int sum = scores[first] + scores[second];

        if (sum >= 10)
        {
            scores.push_back(1);
            scores.push_back(sum % 10);
        }
        else
            scores.push_back(sum);

        first += scores[first] + 1;
        second += scores[second] + 1;

        while (first >= scores.size())
            first = first - scores.size();

        while (second >= scores.size())
            second = second - scores.size();
    }

    for (int i = 0; i < 10; i++)
        std::cout << scores[input + i];

    std::cout << '\n';

    return 0;
}