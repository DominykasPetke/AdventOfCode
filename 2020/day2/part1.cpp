#include <iostream>
#include <fstream>
#include <algorithm>

int main()
{
    std::ifstream in("input");

    int sum = 0;

    std::string line;

    while (std::getline(in, line))
    {
        int min = std::stoi(line);
        int max = std::stoi(line.substr(line.find_first_of('-') + 1));

        char c = *(line.substr(line.find_first_of(':') - 1, 1).c_str());

        std::string text = line.substr(line.find_first_of(':') + 2);

        int count = std::count(text.begin(), text.end(), c);

        if (count <= max && count >= min)
            sum++;
    }

    std::cout << sum << std::endl;

    return 0;
}