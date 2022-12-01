#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <vector>

struct Field
{
    int lowmin;
    int lowmax;
    int himin;
    int himax;

    bool valid(int number)
    {
        return (number >= lowmin && number <= lowmax) || (number >= himin && number <= himax);
    }
};

int main()
{
    std::string line;
    std::ifstream in("input");

    std::vector<Field> fields;

    while (std::getline(in, line)) // first part
    {
        std::smatch match;

        if (!std::regex_search(line, match, std::regex("(\\d+)-(\\d+) or (\\d+)-(\\d+)")))
        {
            std::getline(in, line);
            std::getline(in, line);
            std::getline(in, line);
            std::getline(in, line);
            break;
        }

        fields.push_back({std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3]), std::stoi(match[4])});
    }

    int sum = 0;

    while (std::getline(in, line)) // second part
    {
        std::stringstream ss(std::regex_replace(line, std::regex(","), " "));

        int number;

        while (ss >> number)
        {
            if (![&fields, number]() {
                    for (auto i : fields)
                    {
                        if (i.valid(number))
                        {
                            return true;
                        }
                    }

                    return false;
                }())
            {
                sum += number;
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}