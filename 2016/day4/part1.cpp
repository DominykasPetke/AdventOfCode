#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream in("input");
    std::string line;

    int sum = 0;

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
            sum += id;
    }

    std::cout << sum << '\n';

    return 0;
}