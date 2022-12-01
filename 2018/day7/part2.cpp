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

    std::array<std::pair<int, char>, 5> workers;
    workers.fill({0, '-'}); // fill w/ 0s
    int free_workers = 5;
    int total_time = 0;

    while (data.size() > 0) // while we has data
    {
        // sort data
        std::sort(data.begin(), data.end(), [](std::pair<char, std::string> const &t, std::pair<char, std::string> const &f) {
            if (t.second.size() < f.second.size())
                return true;
            else if (t.second.size() > f.second.size())
                return false;
            else
                return t.first < f.first;
        });

        //assign jobs
        for (int i = 0; i < data.size() && free_workers > 0 && data[i].second.size() == 0; i++)
        {
            free_workers--;
            workers[free_workers] = {data[i].first - 4, data[i].first};
            data.erase(data.begin(), data.begin() + 1); // remove data from vector to not assign same job again
            i--;
        }

        // sort by time
        std::sort(workers.begin(), workers.end(), [](std::pair<int, char> const &t, std::pair<int, char> const &f) {
            if (t.first == 0)
                return true;
            if (f.first == 0)
                return false;
            return t.first > f.first;
        });

        // "simulate" time
        int minus = workers[4].first;
        for (int i = 4; i >= free_workers; i--)
        {
            workers[i].first -= minus;
        }

        free_workers++;

        total_time += minus; // add time

        // remove from dependencies the finished job
        for (auto &i : data)
            if (auto j = i.second.find(workers[4].second); j != std::string::npos)
                i.second.erase(j, 1);

        // sort again so 0 flows to the top
        std::sort(workers.begin(), workers.end(), [](std::pair<int, char> const &t, std::pair<int, char> const &f) {
            if (t.first == 0)
                return true;
            if (f.first == 0)
                return false;
            return t.first > f.first;
        });
    }

    std::sort(workers.begin(), workers.end(), [](std::pair<int, char> const &t, std::pair<int, char> const &f) { return t.first > f.first; }); // last sort to add missing time

    std::cout << total_time + workers[0].first << '\n'; // result output

    return 0;
}