#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <array>
#include <algorithm>

int main()
{
    std::string line;
    std::ifstream in("input");

    std::unordered_map<int, std::array<int, 4>> numbers;
    std::unordered_map<int, std::string> text;

    while (std::getline(in, line))
    {
        std::regex big_boi("^(\\d+): (\"(.)\"|(\\d+)( (\\d+)?( ?\\| (\\d+) ?(\\d+)?)?)?)$");
        std::smatch match;

        if (!std::regex_search(line, match, big_boi))
        {
            break;
        }

        if (match[3].length() == 0)
        {
            numbers[std::stoi(match[1])] = {std::stoi(match[4]),
                                            match[6].length() == 0 ? -1 : std::stoi(match[6]),
                                            match[8].length() == 0 ? -1 : std::stoi(match[8]),
                                            match[9].length() == 0 ? -1 : std::stoi(match[9])};
        }
        else
        {
            text[std::stoi(match[1])] = match[3];
        }
    }

    while (text[0] == "")
    {
        std::vector<int> to_remove;

        for (auto i : numbers)
        {
            if (std::all_of(i.second.begin(), i.second.end(), [&text](int number) {
                    return number == -1 || text[number].length() != 0;
                }))
            {
                text[i.first] += "(";
                text[i.first] += text[i.second[0]];

                if (i.second[1] != -1)
                {
                    text[i.first] += text[i.second[1]];
                }

                if (i.second[2] != -1)
                {
                    text[i.first] += "|";
                    text[i.first] += text[i.second[2]];
                }

                if (i.second[3] != -1)
                {
                    text[i.first] += text[i.second[3]];
                }

                text[i.first] += ")";
                to_remove.push_back(i.first);
            }
        }

        for (int i : to_remove)
        {
            numbers.erase(i);
        }
    }

    int64_t sum = 0;
    std::regex zero("^" + text[0] + "$");

    while (std::getline(in, line))
    {
        if (std::regex_search(line, zero))
        {
            sum++;
        }
    }

    std::cout << sum << '\n';
    return 0;
}