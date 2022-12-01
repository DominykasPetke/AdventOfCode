#include <iostream>
#include <fstream>

int main()
{

    std::string line;
    std::ifstream in("input");

    int x = 0;      // W / E
    int y = 0;      // N / S
    int facing = 1; // NESW

    while (in >> line)
    {
        int number = std::stoi(line.substr(1));

        switch (line[0])
        {
        case 'N':
            y += number;
            break;
        case 'S':
            y -= number;
            break;
        case 'E':
            x += number;
            break;
        case 'W':
            x -= number;
            break;
        case 'L':
            while (number >= 90)
            {
                number -= 90;
                facing--;
            }

            if (facing < 0)
            {
                facing += 4;
            }
            
            break;
        case 'R':
            while (number >= 90)
            {
                number -= 90;
                facing++;
            }

            facing %= 4;
            break;
        case 'F':
            switch (facing)
            {
            case 0:
                y += number;
                break;
            case 1:
                x += number;
                break;
            case 2:
                y -= number;
                break;
            case 3:
                x -= number;

            default:
                break;
            }
        default:
            break;
        }
    }

    std::cout << std::abs(x) + std::abs(y) << '\n';

    return 0;
}