#include <fstream>
#include <iostream>
#include <unordered_set>

int main()
{
    std::unordered_set<int> numbers;

    int number;
    int sum = 0;

    while (1)
    {
        std::ifstream in("input");

        while (in >> number)
        {
            sum += number;

            if (auto search = numbers.find(sum); search != numbers.end())
            {
                std::cout << sum << '\n';
                return 0;
            }
            else
                numbers.insert(sum);
        }
    }
}