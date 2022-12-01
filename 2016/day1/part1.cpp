#include <fstream>
#include <iostream>

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
        case 0:
            NS += number;
            break;
        case 1:
            EW += number;
            break;
        case 2:
            NS -= number;
            break;
        case 3:
            EW -= number;
        default:
            break;
        }
    }

    std::cout << std::abs(EW) + std::abs(NS) << '\n';

    return 0;
}