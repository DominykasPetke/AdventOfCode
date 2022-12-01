#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main()
{
    std::unordered_map<std::string, std::unordered_map<std::string, int>> possibilities;

    {
        std::string line;
        std::ifstream in("input");

        while (std::getline(in, line))
        {
            std::stringstream ss(line);
            std::string word;
            std::vector<std::string> words;

            while (ss >> word && word[0] != '(')
            {
                words.push_back(word);
            }

            while (ss >> word)
            {
                std::string all = word.substr(0, word.length() - 1);

                for (auto const &i : words)
                {
                    possibilities[all][i]++;
                }
            }
        }
    }

    std::unordered_map<std::string, std::vector<std::string>> maximums;

    for (auto const &i : possibilities)
    {
        int max = 0;
        std::vector<std::string> ingredients;

        for (auto const &j : i.second)
        {
            if (j.second > max)
            {
                max = j.second;
                ingredients.clear();
                ingredients.push_back(j.first);
            }
            else if (j.second == max)
            {
                ingredients.push_back(j.first);
            }
        }

        maximums[i.first] = ingredients;
    }

    std::map<std::string, std::string> allergens;

    while (maximums.size() > 0)
    {
        std::vector<std::string> to_erase;

        for (auto i : maximums)
        {
            if (i.second.size() == 1)
            {
                allergens[i.first] = (i.second.front());
                to_erase.push_back(i.first);

                for (auto &j : maximums)
                {
                    auto a = std::find(j.second.begin(), j.second.end(), allergens[i.first]);

                    if (a != std::end(j.second))
                    {
                        j.second.erase(a);
                    }
                }
            }
        }

        for (auto i : to_erase)
        {
            maximums.erase(i);
        }
    }

    std::string output;

    for (auto i : allergens)
    {
        output += i.second + ',';
    }

    std::cout << output.substr(0, output.length() - 1) << '\n';

    return 0;
}