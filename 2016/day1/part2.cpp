#include <fstream>
#include <iostream>
#include <set>
#include <functional>

bool readData(std::ifstream &input, std::string &output)
{
    if (input >> output)
    {
        if (output.back() == ',')
            output.erase(output.size() - 1, 1);
        return true;
    }
    else
        return false;
}

bool check(std::function<void()> const &func, int const &NS, int const &EW, int counter, std::set<std::pair<int, int>> &locations)
{
    while (counter > 0)
    {
        func();

        if (auto search = locations.find({NS, EW}); search == locations.end())
            locations.insert({NS, EW});
        else
        {
            std::cout << std::abs(EW) + std::abs(NS) << '\n';
            return true;
        }

        counter--;
    }

    return false;
}

int main()
{
    // 0 - north
    // 1 - east
    // 2 - south
    // 3 - west

    int NS = 0, EW = 0;
    int facing = 0;
    std::string text;
    std::ifstream in("input");
    std::set<std::pair<int, int>> locations;

    while (readData(in, text))
    {
        switch (text.front())
        {
        case 'L':
            if (facing == 0)
                facing = 3;
            else
                facing--;
            break;

        case 'R':
            if (facing == 3)
                facing = 0;
            else
                facing++;
        default:
            break;
        }

        text.erase(0, 1);
        int number = std::stoi(text);

        switch (facing)
        {
        case 0: // north
            if (check([&NS]() { NS++; }, NS, EW, number, locations))
                return 0;

            break;
        case 1: // east
            if (check([&EW]() { EW++; }, NS, EW, number, locations))
                return 0;

            break;
        case 2: // south
            if (check([&NS]() { NS--; }, NS, EW, number, locations))
                return 0;

            break;
        case 3: // west
            if (check([&EW]() { EW--; }, NS, EW, number, locations))
                return 0;
        default:
            break;
        }
    }

    return 0;
}