#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> numbers;

    {
        std::ifstream in("input");
        int number;

        while (in >> number)
        {
            numbers.push_back(number);
        }

        numbers.push_back(0);
    }

    std::sort(numbers.begin(), numbers.end());

    int ones = 0;
    int threes = 1;

    for (std::size_t i = 1; i < numbers.size(); i++)
    {
        int diff = numbers[i] - numbers[i - 1];
        
        switch (diff)
        {
        case 3:
            threes++;
            break;
        case 1:
            ones++;
        default:
            break;
        }
    }

    std::cout << ones * threes << '\n';
}