#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream in("input");
    std::string line;

    std::vector<std::pair<std::string, int>> real_ones;

    while (in >> line)
    {
        std::string checksum = line.substr(line.find_last_of('-') + 1);
        line.erase(line.begin() + line.find_last_of('-'), line.end());

        int id = std::stoi(checksum);

        checksum.erase(checksum.begin(), checksum.begin() + checksum.find('[') + 1);
        checksum.erase(checksum.end() - 1);

        std::vector<std::pair<char, int>> amounts;

        for (char i = 'a'; i <= 'z'; i++)
            amounts.push_back({i, std::count(line.begin(), line.end(), i)});

        std::sort(amounts.begin(), amounts.end(), [](std::pair<char, int> const &t, std::pair<char, int> const &f) {
            if (t.second > f.second)
                return true;
            if (t.second < f.second)
                return false;
            if (t.first < f.first)
                return true;
            return false;
        });

        std::string first_five = "";
        first_five += amounts[0].first;
        first_five += amounts[1].first;
        first_five += amounts[2].first;
        first_five += amounts[3].first;
        first_five += amounts[4].first;

        if (first_five == checksum)
            real_ones.push_back({line, id});
    }

    for (auto i : real_ones)
    {
        int move_forward = i.second % 26;

        for (auto &j : i.first)
            if (j == '-')
                j = ' ';
            else
                for (int k = 0; k < move_forward; k++) // had to do it one by one cuz nasty bug if j goes over 127 and I cba to think how to fix it
                {
                    j++;
                    if (j > 'z')
                        j = 'a';
                }

        if (i.first.substr(0, 5) == "north")
            std::cout << i.second << '\n';
    }

    return 0;
}