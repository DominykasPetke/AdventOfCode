#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("input");

    int prev = 0;
    int number = 0;
    int increases = 0;

    while (in >> number) {
        if (prev == 0) {
            prev = number;
        }

        if (prev < number) {
            increases++;
        }

        prev = number;
    }

    std::cout << increases << '\n';

    return 0;
}