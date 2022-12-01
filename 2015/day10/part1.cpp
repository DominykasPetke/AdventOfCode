#include <iostream>
#include <fstream>

int main()
{
    std::string digit;

    {
        std::ifstream in("input");
        in >> digit;
    }

    for (short i = 0; i < 40; i++)
    {
        std::string new_digit = "";
        char previous = digit[0];
        int count = 0;

        for (char j : digit)
        {
            if (j == previous)
            {
                count++;
            }
            else
            {
                new_digit += count + '0';
                new_digit += previous;
                count = 1;
                previous = j;
            }
        }

        new_digit += count + '0';
        new_digit += previous;

        digit = new_digit;
    }

    std::cout << digit.size() << '\n';

    return 0;
}