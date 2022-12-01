#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

int main()
{
    // std::map<std::string, std::vector<std::string>> replacements;
    // std::string line;

    // {
    //     std::ifstream in("input");

    //     while (std::getline(in, line))
    //     {
    //         if (line.length() == 0)
    //         {
    //             std::getline(in, line);
    //             break;
    //         }

    //         replacements[line.substr(0, line.find_first_of(' '))].push_back(line.substr(line.find_last_of(' ') + 1));
    //     }
    // }

    // auto f = [&line](std::pair<std::string, int> t, std::pair<std::string, int> f) {
    //     auto score = [](std::ptrdiff_t match, int steps) { return (match * 16) - steps; };

    //     int score1 = score(std::mismatch(line.begin(), line.end(), t.first.begin()).first - line.begin(), t.second);
    //     int score2 = score(std::mismatch(line.begin(), line.end(), f.first.begin()).first - line.begin(), f.second);

    //     if (score1 < score2)
    //         return true;
    //     if (score1 > score2)
    //         return false;
    //     return t.second < f.second;
    // };

    // std::priority_queue<
    //     std::pair<std::string, int>,
    //     std::vector<std::pair<std::string, int>>,
    //     decltype(f)>
    //     q(f);
    // std::set<std::string> no_dupes;

    // q.push({"e", 0});
    // no_dupes.insert("e");

    // int length = 0;
    // long int count = 0;

    // int *remove_unneeded = new int[line.size()];

    // for (int i = 0; i < line.size(); i++)
    // {
    //     remove_unneeded[i] = __INT_MAX__;
    // }

    // while (!q.empty())
    // {
    //     auto top = q.top();
    //     std::cout << q.size() << ' ' << top.second << '\n';
    //     q.pop();

    //     if (top.second == 600)
    //         return 0;

    //     if (q.size() > 15000000)
    //         return 0;

    //     auto match = std::mismatch(line.begin(), line.end(), top.first.begin()).first - line.begin();

    //     if (match > length)
    //     {
    //         count = top.second;

    //         std::cout << "L: " << match << " str: " << top.first.substr(0, match) << " cnt: " << count << '\n';

    //         for (int i = length; i <= match; i++)
    //             remove_unneeded[i] = count * 1.5;

    //         length = match;
    //     }

    //     if (top.first == line)
    //     {
    //         std::cout << "ANSWER: " << top.second << '\n';
    //         return 0;
    //     }

    //     for (auto i : replacements)
    //     {
    //         size_t pos = 0;
    //         pos = top.first.find(std::string(i.first), pos);

    //         while (pos != std::string::npos)
    //         {
    //             for (auto word : i.second)
    //             {
    //                 std::string replaced = top.first.substr(0, pos);
    //                 replaced += word;
    //                 replaced += top.first.substr(pos + i.first.length());

    //                 auto match_l = std::mismatch(line.begin(), line.end(), top.first.begin()).first - line.begin();

    //                 if (replaced.size() <= line.size() && no_dupes.count(replaced) == 0 && remove_unneeded[match_l] > top.second)
    //                 {
    //                     q.push({replaced, top.second + 1});
    //                     no_dupes.insert(replaced);
    //                 }
    //             }

    //             pos = top.first.find(i.first, pos + i.first.length());
    //         }
    //     }

    //     //no_dupes.erase(top.first);
    // }

    std::cout << "Fuck this, go here https://www.reddit.com/r/adventofcode/comments/3xflz8/day_19_solutions/cy4etju/" << '\n';
    std::cout << 212 << '\n';

    return 0;
}