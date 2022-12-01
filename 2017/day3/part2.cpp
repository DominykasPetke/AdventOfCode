#include <iostream>
#include <cmath>

#define INPUT 289326

constexpr int sum(const int index)
{
    if (index == 0)
        return 1;
    if (index == 1)
        return sum(index - 1);
    if (index == 2)
        return sum(index - 1) * 2;
    if (index == 3)
        return sum(index - 1) * 2;
    if (index == 4)
        return sum(index - 1) + sum(index - 4);
    if (index == 5)
        return sum(index - 1) * 2;
    if (index == 6)
        return sum(index - 1) + sum(index - 5);
    if (index == 7)
        return sum(index - 1) * 2 + sum(index - 6);

    int base = 8;
    bool one = false;
    int next = 10;
    int inc = 3;

    while (next < index)
    {
        if (one)
        {
            one = false;
            inc++;
        }
        else
            one = true;
        next += inc;
        base += 2;
    }

    if (index == next)
        return sum(index - 1) * 2 + sum(index - base);
    if (index == next - 1)
        return sum(index - 1) + sum(index - base);
    if (index == next - 2)
        return sum(index - 1) + sum(index - base) + sum(index - base + 1);
    return sum(index - 1) + sum(index - base) + sum(index - base + 1) + sum(index - base + 2);
}

int main()
{
    int i = 0;

    while (sum(i) < INPUT)
        i++;

    std::cout << sum(i) << '\n';

    return 0;
}