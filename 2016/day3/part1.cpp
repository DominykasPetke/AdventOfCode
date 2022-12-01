#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("input");

    int sum = 0;

    while (!in.eof())
    {
        int a, b, c;
        in >> a >> b >> c;

        if (a + b > c && b + c > a && a + c > b)
            sum++;
    }

    std::cout << sum << '\n';

    return 0;
}