#include <iostream>
#include <fstream>

int main()
{

    std::string line;
    std::ifstream in("input");

    int x = 0; // W / E
    int y = 0; // N / S
    int waypointX = 10;
    int waypointY = 1;

    while (in >> line)
    {
        int number = std::stoi(line.substr(1));

        switch (line[0])
        {
        case 'N':
            waypointY += number;
            break;
        case 'S':
            waypointY -= number;
            break;
        case 'E':
            waypointX += number;
            break;
        case 'W':
            waypointX -= number;
            break;
        case 'L':
            while (number >= 90)
            {
                int newX = waypointY >= 0 ? -waypointY : waypointY * -1;
                int newY = waypointX;

                waypointX = newX;
                waypointY = newY;

                number -= 90;
            }

            break;
        case 'R':
            while (number >= 90)
            {
                int newX = waypointY;
                int newY = waypointX >= 0 ? -waypointX : waypointX * -1;

                waypointX = newX;
                waypointY = newY;

                number -= 90;
            }

            break;
        case 'F':
            x += waypointX * number;
            y += waypointY * number;
            break;
        default:
            break;
        }
    }

    std::cout << std::abs(x) + std::abs(y) << '\n';

    return 0;
}