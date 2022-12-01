#include <iostream>
#include <fstream>

int main()
{
    int sum = 0;

    std::ifstream in("input");

    int number;

    while (in >> number)
    {
        int fuel = number / 3 - 2;
        
        while (fuel > 0)
        {
            sum += fuel;
            fuel = fuel / 3 - 2;
        }
    }

    std::cout << sum << '\n';

    return 0;
}