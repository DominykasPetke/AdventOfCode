#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

int main()
{
    std::ifstream in("input");

    int threes = 0, twos = 0;

    std::string temp;

    while (in >> temp)
    {
        std::array<int, 26> count;
        count.fill(0);

        for (auto i : temp)
            count[i - 'a']++;

        if (std::any_of(count.begin(), count.end(), [](const int a) { return a == 2; }))
            twos++;

        if (std::any_of(count.begin(), count.end(), [](const int a) { return a == 3; }))
            threes++;
    }

    std::cout << twos * threes << '\n';

    return 0;
}