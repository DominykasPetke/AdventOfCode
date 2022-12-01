#include <iostream>
#include <fstream>

int main()
{
    std::string text;
    std::ifstream in("input");

    int x = 0, y = 2;

    while (in >> text)
    {
        for (auto i : text)
        {
            switch (i)
            {
            case 'U':
                switch (x)
                {
                case 2:
                    if (y > 0)
                        y--;
                    break;
                case 1:
                case 3:
                    if (y > 1)
                        y--;
                case 0:
                case 4:
                default:
                    break;
                }
                break;

            case 'L':
                switch (y)
                {
                case 2:
                    if (x > 0)
                        x--;
                    break;
                case 1:
                case 3:
                    if (x > 1)
                        x--;
                case 0:
                case 4:
                default:
                    break;
                }
                break;

            case 'D':
                switch (x)
                {
                case 2:
                    if (y < 4)
                        y++;
                    break;
                case 1:
                case 3:
                    if (y < 3)
                        y++;
                case 0:
                case 4:
                default:
                    break;
                }
                break;

            case 'R':
                switch (y)
                {
                case 2:
                    if (x < 4)
                        x++;
                    break;
                case 1:
                case 3:
                    if (x < 3)
                        x++;
                case 0:
                case 4:
                default:
                    break;
                }

            default:
                break;
            }
        }

        std::cout << "  1   234 56789 ABC   D  "[y * 5 + x];
    }

    std::cout << '\n';

    return 0;
}