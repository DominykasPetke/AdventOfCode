#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

int main()
{
    std::map<std::string, std::map<std::string, int>> happinesses;

    {
        std::ifstream in("input");
        std::string line = "";

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

            std::string first = values[0];
            std::string second = values[10];
            second = second.substr(0, second.length());
            second.erase(second.size() - 1);

            int happy = std::stoi(values[3]);

            if (values[2] == "lose")
            {
                happy *= -1;
            }

            happinesses[first][second] += happy;
            happinesses[second][first] += happy;
        }
    }

    for (auto i : happinesses)
    {
        happinesses["Petke"][i.first] = 0;
        happinesses[i.first]["Petke"] = 0;
    }

    auto f = [](std::pair<std::vector<std::string>, int> t, std::pair<std::vector<std::string>, int> f) {
        if (t.first.size() == f.first.size())
            return t.second < f.second;
        return t.first.size() > f.first.size();
    };

    std::priority_queue<
        std::pair<std::vector<std::string>, int>,
        std::vector<std::pair<std::vector<std::string>, int>>,
        decltype(f)>
        queue(f);

    for (auto i : happinesses)
    {
        for (auto j : i.second)
        {
            queue.push({{i.first, j.first}, j.second});
        }
    }

    auto top = queue.top();

    while (top.first.size() != happinesses.size())
    {
        for (auto i : happinesses[top.first.back()])
        {
            if (std::find(top.first.begin(), top.first.end(), i.first) == top.first.end())
            {
                std::pair<std::vector<std::string>, int> copy = {top.first, top.second};

                top.first.push_back(i.first);
                top.second += i.second;

                if (top.first.size() == happinesses.size())
                {
                    top.second += happinesses[top.first.front()][top.first.back()];
                }

                queue.push(top);

                top = {copy.first, copy.second};
            }
        }

        queue.pop();
        top = queue.top();
    }

    std::cout << top.second << '\n';

    return 0;
}