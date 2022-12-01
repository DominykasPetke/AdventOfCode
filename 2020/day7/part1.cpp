#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <queue>

int main()
{
    std::ifstream in("input");
    std::string line;

    std::unordered_map<std::string, std::vector<std::string>> bags;

    while (std::getline(in, line))
    {
        std::regex outer("^(.*?) bags contain ");

        std::smatch res;
        std::regex_search(line, res, outer);

        std::string outer_bag = res[1];
        line = line.substr(res.length());

        std::regex bagger("\\d+ (.*?) bag");

        while (std::regex_search(line, res, bagger))
        {
            bags[res[1]].push_back(outer_bag);
            line = line.substr(res.length());
        }
    }

    std::unordered_map<std::string, bool> exists;
    std::queue<std::string> queue;

    queue.push("shiny gold");

    while (!queue.empty())
    {
        std::string top = queue.front();
        queue.pop();

        for (auto i : bags[top])
        {
            if (!exists[i])
            {
                exists[i] = 1;
                queue.push(i);
            }
        }
    }

    std::cout << exists.size() << std::endl;

    return 0;
}