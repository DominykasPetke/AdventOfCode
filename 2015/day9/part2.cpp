#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

int main()
{
    std::map<std::string, std::map<std::string, int>> paths;

    {
        std::ifstream in("input");
        std::string line = "";

        while (std::getline(in, line))
        {
            std::string start = line.substr(0, line.find(' '));
            std::string end = line.substr(line.find(' ') + 4, line.find_last_of(" = ") - line.find(' ') - 6);

            int dist = std::stoi(line.substr(line.find_last_of(" = ")));

            paths[start][end] = dist;
            paths[end][start] = dist;
        }
    }

    auto f = [](std::pair<std::vector<std::string>, int> t, std::pair<std::vector<std::string>, int> f) { return t.second > f.second; };

    std::priority_queue<
        std::pair<std::vector<std::string>, int>,
        std::vector<std::pair<std::vector<std::string>, int>>, decltype(f)>
        queue(f);

    for (auto i : paths)
    {
        for (auto j : i.second)
        {
            queue.push({{i.first, j.first}, j.second});
        }
    }

    auto top = queue.top();

    while (queue.size() > 0)
    {
        if (top.first.size() != paths.size())
        {
            for (auto i : paths[top.first.back()])
            {
                if (std::find(top.first.begin(), top.first.end(), i.first) == top.first.end())
                {
                    top.first.push_back(i.first);
                    top.second += i.second;
                    queue.push(top);
                    top = queue.top();
                }
            }

            queue.pop();
            top = queue.top();
        }
        else
        {
            queue.pop();
            top = queue.top();
        }
    }

    std::cout << top.second << '\n';

    return 0;
}