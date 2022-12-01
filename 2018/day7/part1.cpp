#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

int main()
{
    std::vector<std::pair<char, std::string>> data;

    { // input data
        std::ifstream in("input");

        std::map<char, std::string> prereqs;

        std::string line;

        while (std::getline(in, line))
            prereqs[line[36]] += line[5];

        for (char i = 'A'; i <= 'Z'; i++)
            data.push_back({i, prereqs[i]});
    }

    while (data.size() > 0)
    {
        std::sort(data.begin(), data.end(), [](std::pair<char, std::string> const &t, std::pair<char, std::string> const &f) { // sort by prerequisites amount then alphabet
            if (t.second.size() < f.second.size())
                return true;
            else if (t.second.size() > f.second.size())
                return false;
            else
                return t.first < f.first;
        });

        std::cout << data[0].first; // output result letter

        for (auto &i : data) // erase dependancy from further jobs
            if (auto j = i.second.find(data[0].first); j != std::string::npos)
                i.second.erase(j, 1);

        data.erase(data.begin(), data.begin() + 1); // and remove current job
    }

    std::cout << '\n';

    return 0;
}