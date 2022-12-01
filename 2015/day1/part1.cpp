#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("input");

    char temp;
    int floor = 0;

    while (in >> temp)
        if (temp == '(')
            floor++;
        else if (temp == ')')
            floor--;

    std::cout << floor << '\n';

    return 0;
}