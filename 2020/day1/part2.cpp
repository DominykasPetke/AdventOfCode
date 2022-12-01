#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream in("input");
    std::vector<int> numbers;

    int number;

    while (in >> number)
    {
        numbers.push_back(number);
    }

    for (int i : numbers)
    {
        for (int j : numbers)
        {
            for (int k : numbers)
            {
                if (i + j + k == 2020)
                {
                    std::cout << i * j * k << '\n';
                    return 0;
                }
            }
        }
    }

    return 0;
}