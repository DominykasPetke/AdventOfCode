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

    std::sort(numbers.begin(), numbers.end());

    std::vector<int>::iterator forw_it = numbers.begin();
    std::vector<int>::reverse_iterator back_it = numbers.rbegin();

    int sum = *forw_it + *back_it;

    while (sum != 2020)
    {
        if (sum > 2020)
        {
            back_it++;
        }

        if (sum < 2020)
        {
            forw_it++;
        }

        sum = *forw_it + *back_it;
    }

    std::cout << *forw_it * *back_it << '\n';

    return 0;
}