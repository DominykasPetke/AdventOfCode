#include <iostream>
#include <fstream>
#include <sstream>

int main()
{

    std::string line;
    std::ifstream in("input");

    int counter = 0;

    while (std::getline(in, line))
    {
        std::stringstream input(line);

        std::string digit;

        for (int i = 0; i < 11; i++)
        {
            input >> digit;
        }

        for (int i = 0; i < 4; i++)
        {
            input >> digit;

            switch (digit.length())
            {
            case 2:
            case 3:
            case 4:
            case 7:
                counter++;
                break;

            default:
                break;
            }
        }
    }

    std::cout << counter << '\n';

    return 0;
}