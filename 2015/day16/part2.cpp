#include <fstream>
#include <iostream>
#include <vector>
#include <map>

bool check_value(std::string name, int count)
{
    const std::map<std::string, int> actual = {{"children:", 3},
                                               {"cats:", 7},
                                               {"samoyeds:", 2},
                                               {"pomeranians:", 3},
                                               {"akitas:", 0},
                                               {"vizslas:", 0},
                                               {"goldfish:", 5},
                                               {"trees:", 3},
                                               {"cars:", 2},
                                               {"perfumes:", 1}};

    if (name == "cats:" || name == "trees:")
    {
        return actual.at(name) < count;
    }

    if (name == "pomeranians:" || name == "goldfish:")
    {
        return actual.at(name) > count;
    }

    return actual.at(name) == count;
}

int main()
{

    std::ifstream in("input");
    std::string line;

    while (std::getline(in, line))
    {
        std::vector<std::string> values = [&line]() {
            size_t pos = 0;
            std::string token;

            std::vector<std::string> ret;

            while ((pos = line.find(" ")) != std::string::npos)
            {
                token = line.substr(0, pos);
                ret.push_back(token);
                line.erase(0, pos + 1);
            }

            ret.push_back(line);

            return ret;
        }();

        if (check_value(values[2], std::stoi(values[3])) &&
            check_value(values[4], std::stoi(values[5])) &&
            check_value(values[6], std::stoi(values[7])))
        {
            std::cout << std::stoi(values[1]) << '\n';
        }
    }

    return 0;
}