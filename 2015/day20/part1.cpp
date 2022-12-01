#include <iostream>
#include <fstream>
#include <cmath>

int sumDivisors(int n)
{
    int sum = 0;

    for (int i = 1; i <= std::sqrt(n); i++)
    {
        if (n % i == 0)
        {
            sum += i;

            if (n / i != i)
            {
                sum += n / i;
            }
        }
    }

    return sum;
}

int main()
{
    int number;

    std::ifstream in("input");
    in >> number;

    for (int i = 0; i < __INT_MAX__; i++)
    {
        if (sumDivisors(i) * 10 > number)
        {
            std::cout << i << '\n';
            return 0;
        }
    }

    return 0;
}