#include <iostream>
#include <fstream>

int main()
{
    std::string text;
    std::ifstream in("input");

    int x = 1, y = 1;

    while (in >> text)
    {
        for (auto i : text)
        {
            switch (i)
            {
            case 'U':
                if (y > 0)
                    y--;
                break;
            case 'L':
                if (x > 0)
                    x--;
                break;
            case 'D':
                if (y < 2)
                    y++;
                break;
            case 'R':
                if (x < 2)
                    x++;
            default:
                break;
            }
        }

        std::cout << y * 3 + x + 1;
    }

    std::cout << '\n';

    return 0;
}