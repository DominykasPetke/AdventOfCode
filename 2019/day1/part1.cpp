#include <iostream>
#include <fstream>

int main()
{
    int sum = 0;

    std::ifstream in("input");

    int number;

    while (in >> number)
    {
        sum += number / 3 - 2;
    }

    std::cout << sum << '\n';

    return 0;
}