#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("input");

    std::string line;

    in >> line;

    for (int i = 1; i < line.length(); i++)
        if ((std::toupper(line[i]) == line[i - 1] || line[i] == toupper(line[i - 1])) && line[i] != line[i - 1])
        {
            line.erase(i - 1, 2);
            i -= 2;
        }

    std::cout << line.length() << '\n';

    return 0;
}