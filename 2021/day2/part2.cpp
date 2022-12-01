#include <iostream>
#include <fstream>

int main()
{
    std::string line;
    int number;

    std::ifstream in("input");

    int hor = 0;
    int depth = 0;
    int aim = 0;

    while (in >> line >> number)
    {
        switch (line[0])
        {
        case 'f':
            hor += number;
            depth += number * aim;
            break;
        case 'u':
            aim -= number;
            break;
        case 'd':
            aim += number;
        default:
            break;
        }
    }

    std::cout << hor * depth << '\n';

    return 0;
}