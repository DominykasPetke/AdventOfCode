#include <iostream>
#include <fstream>

int main()
{
    std::string number;
    std::ifstream in("input");

    in >> number;

    int sum = 0;

    for (std::size_t i = 0, length = number.length() / 2; i < length; i++)
        if (number[i] == number[i + length])
            sum += number[i] - '0';

    std::cout << sum * 2 << '\n';

    return 0;
}