#include <iostream>
#include <fstream>
#include <unordered_map>

int main()
{
    std::ifstream in("input");
    int sum = 0;
    std::string line;

    std::unordered_map<char, int> counts;

    while (std::getline(in, line))
    {
        if (line == "")
        {
            sum += counts.size();
            counts.clear();
        }
        else
        {
            for (char c : line)
            {
                counts[c]++;
            }
        }
    }

    std::cout << sum + counts.size() << std::endl;

    return 0;
}