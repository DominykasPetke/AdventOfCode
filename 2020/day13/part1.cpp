#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

int main()
{
    std::string line;
    std::ifstream in("input");

    int target;
    in >> target;

    in >> line >> line;

    line = std::regex_replace(line, std::regex(","), " ");
    line = std::regex_replace(line, std::regex("x"), "");

    std::stringstream ss(line);

    int number;

    int id = 0;
    int min = INT32_MAX;

    while (ss >> number)
    {
        int calc = number - (target % number);

        if (calc < min)
        {
            min = calc;
            id = number;
        }
    }

    std::cout << min * id << '\n';

    return 0;
}