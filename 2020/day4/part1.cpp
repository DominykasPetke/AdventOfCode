#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main()
{
    std::ifstream in("input");
    int sum = 0;
    std::string line;

    std::vector<std::string> fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

    bool exists[] = {0, 0, 0, 0, 0, 0, 0, 0};

    while (std::getline(in, line))
    {
        if (line == "")
        {
            int count = 0;

            for (int i = 0; i < 7; i++)
            {
                if (exists[i])
                {
                    count++;
                }

                exists[i] = 0;
            }

            if (count == 7)
            {
                sum++;
            }
        }
        else
        {
            std::stringstream out = std::stringstream(line);

            std::string field;

            while (out >> field)
            {
                int num = std::find(fields.begin(), fields.end(), field.substr(0, field.find(':'))) - fields.begin();

                exists[num] = 1;
            }
        }
    }

    int count = 0;

    for (int i = 0; i < 7; i++)
    {
        if (exists[i])
        {
            count++;
        }
    }

    if (count == 7)
    {
        sum++;
    }

    std::cout << sum << std::endl;

    return 0;
}