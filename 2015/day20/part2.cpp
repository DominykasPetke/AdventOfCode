#include <iostream>
#include <fstream>
#include <cmath>

int sumDivisorsPart2(int n)
{
    int sum = 0;

    for (int i = 1; i <= std::sqrt(n); i++)
    {
        if (n % i == 0)
        {
            if (i * 50 >= n)
                sum += i;

            if (n / i != i && n / i * 50 >= n)
                sum += n / i;
        }
    }

    return sum;
}

int main()
{
    int number;

    std::ifstream in("input");
    in >> number;

    for (int i = 1; i < __INT_MAX__; i++)
    {
        if (sumDivisorsPart2(i) * 11 > number)
        {
            std::cout << i << '\n';
            return 0;
        }
    }

    return 0;
}