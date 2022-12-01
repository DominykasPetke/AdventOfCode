#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>

int main()
{
    std::map<std::string, std::vector<std::string>> replacements;
    std::string line;

    {
        std::ifstream in("input");

        while (std::getline(in, line))
        {
            if (line.length() == 0)
            {
                std::getline(in, line);
                break;
            }

            replacements[line.substr(0, line.find_first_of(' '))].push_back(line.substr(line.find_last_of(' ') + 1));
        }
    }

    std::set<std::string> answers;

    for (auto i : replacements)
    {
        size_t pos = 0;
        pos = line.find(std::string(i.first), pos);

        while (pos != std::string::npos)
        {
            for (auto word : i.second)
            {
                std::string replaced = line.substr(0, pos);
                replaced += word;
                replaced += line.substr(pos + i.first.length());

                if (answers.count(replaced) == 0)
                {
                    answers.insert(replaced);
                }
            }

            pos = line.find(i.first, pos + i.first.length());
        }
    }

    std::cout << answers.size() << '\n';

    return 0;
}