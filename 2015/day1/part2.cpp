#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("input");

    char temp;
    int floor = 0;
    int counter = 1;

    while (in >> temp) {
        if (temp == '(')
            floor++;
        else if (temp == ')')
            floor--;

        if (floor == -1) {
            std::cout << counter << '\n';
            return 0;
        }
        
        counter++;
    }

    std::cout << "Failed.\n";

    return 0;
}