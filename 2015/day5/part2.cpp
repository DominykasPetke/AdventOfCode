#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("input");

    int nice = 0;
    std::string str;

    while (in >> str)
    {
        bool gap = false, pair = false;

        for (unsigned int i = 0; i < str.length() - 2; i++)
            if (str[i] == str[i + 2])
            {
                gap = true;
                break;
            }

        for (unsigned int i = 0; i < str.length() - 3; i++)
            for (unsigned int j = i + 2; j < str.length() - 1; j++)
                if (str[i] == str[j] && str[i + 1] == str[j + 1])
                {
                    pair = true;
                    i = str.length();
                    break;
                }

        if (gap && pair)
            nice++;
    }

    std::cout << nice << '\n';

    return 0;
}