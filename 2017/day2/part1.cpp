#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

int main()
{
    std::ifstream in("input");
    std::string line;
    int sum = 0;

    while (std::getline(in, line))
    {
        std::stringstream stream(line);

        std::vector<int> row;
        int temp;

        while (stream >> temp)
            row.push_back(temp);

        std::sort(row.begin(), row.end());

        sum += row.back() - row.front();
    }

    std::cout << sum << '\n';

    return 0;
}