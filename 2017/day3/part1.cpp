#include <iostream>
#include <cmath>

#define INPUT 289326

int main()
{
    const int root = std::sqrt(INPUT);
    int input = INPUT - root * root - 1;

    int x = root / 2 + 1, y = root / 2;

    if (root < input)
    {
        y -= root;
        input -= root;
    }
    else
        y -= input;

    if (root < input)
    {
        x -= root;
        input -= root;
    }
    else
        x -= input;

    if (root < input)
    {
        y += root;
        input -= root;
    }
    else
        y += input;

    x += input;

    std::cout << std::abs(y) + std::abs(x) << '\n';

    return 0;
}