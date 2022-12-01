#include <fstream>
#include <iostream>
#include <algorithm>

int main()
{
    std::ifstream in("input");

    int nice = 0;
    std::string str;
    while (in >> str)
    {
        if (str.find("ab") != std::string::npos ||
            str.find("cd") != std::string::npos ||
            str.find("pq") != std::string::npos ||
            str.find("xy") != std::string::npos)
            continue;

        if (std::adjacent_find(str.begin(), str.end()) == str.end())
            continue;

        if (std::count_if(str.begin(), str.end(), [](char const a) { return a == 'a' || a == 'u' || a == 'i' || a == 'e' || a == 'o'; }) < 3)
            continue;

        nice++;
    }

    std::cout << nice << '\n';

    return 0;
}