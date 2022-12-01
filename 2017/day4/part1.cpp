#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream in("input");
    std::string line;

    int count = 0;

    while (std::getline(in, line))
    {
        std::stringstream stream(line);
        std::vector<std::string> words;
        std::string temp;

        while (stream >> temp)
            words.push_back(temp);

        if (std::sort(words.begin(), words.end()); std::adjacent_find(words.begin(), words.end()) == words.end())
            count++;
    }

    std::cout << count << '\n';

    return 0;
}