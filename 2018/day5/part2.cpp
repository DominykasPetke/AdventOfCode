#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream in("input");
    std::string line;

    in >> line;

    int lowest = 60000;

    for (char i = 'A'; i <= 'Z'; i++)
    {
        std::string copy = line;

        for (int j = 0; j < copy.length(); j++)
            if (std::toupper(copy[j]) == i)
            {
                copy.erase(j, 1);
                j--;
            }

        for (int j = 1; j < copy.length(); j++)
            if (copy[j - 1] != copy[j] && (std::toupper(copy[j - 1]) == copy[j] || std::toupper(copy[j]) == copy[j - 1]))
            {
                copy.erase(j - 1, 2);
                j -= 2;
            }

        if (copy.length() < lowest)
            lowest = copy.length();
    }

    std::cout << lowest << '\n';

    return 0;
}