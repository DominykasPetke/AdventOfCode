#include <iostream>
#include <fstream>
#include <algorithm>

int main()
{
    std::string number;
    std::ifstream in("input");

    in >> number;

    int sum = number.back() == number.front() ? number.front() - '0' : 0;

    std::string::iterator found = std::adjacent_find(number.begin(), number.end());

    while (found != number.end())
    {
        sum += found[0] - '0';

        found = std::adjacent_find(found + 1, number.end());
    }

    std::cout << sum << '\n';

    return 0;
}