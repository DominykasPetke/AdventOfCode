#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_map>

int count_bags(std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> &bags, std::string const &bag)
{
    int sum = 0;

    for (auto i : bags[bag])
    {
        sum += i.first + i.first * count_bags(bags, i.second);
    }

    return sum;
}

int main()
{
    std::ifstream in("input");
    std::string line;

    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> bags;

    while (std::getline(in, line))
    {
        std::regex outer("^(.*?) bags contain ");

        std::smatch res;
        std::regex_search(line, res, outer);

        std::string outer_bag = res[1];
        line = line.substr(res.length());

        std::regex bagger("(\\d+) (.*?) bag");
        std::vector<std::string> containees;

        while (std::regex_search(line, res, bagger))
        {
            bags[outer_bag].push_back({std::stoi(res[1]), res[2]});
            line = line.substr(res.length());
        }
    }

    std::cout << count_bags(bags, "shiny gold") << '\n';

    return 0;
}