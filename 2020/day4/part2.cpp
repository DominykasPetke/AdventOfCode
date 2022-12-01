#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <regex>

bool byr(std::string in)
{
    int yr = std::stoi(in);

    return yr >= 1920 && yr <= 2002;
}

bool iyr(std::string in)
{
    int yr = std::stoi(in);

    return yr >= 2010 && yr <= 2020;
}

bool eyr(std::string in)
{
    int yr = std::stoi(in);

    return yr >= 2020 && yr <= 2030;
}

bool hgt(std::string in)
{
    if (in.ends_with("in"))
    {
        int hg = std::stoi(in);

        return hg >= 59 && hg <= 76;
    }

    if (in.ends_with("cm"))
    {
        int hg = std::stoi(in);

        return hg >= 150 && hg <= 193;
    }

    return 0;
}

bool hcl(std::string in)
{
    std::regex reg("^#[0-9a-f]{6}$");

    return std::regex_search(in, reg);
}

bool ecl(std::string in)
{
    std::vector<std::string> fields = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

    return std::find(fields.begin(), fields.end(), in) != std::end(fields);
}

bool pid(std::string in)
{
    std::regex reg("^[0-9]{9}$");

    return std::regex_search(in, reg);
}

bool cid(std::string in)
{
    return 1;
}

int main()
{
    std::ifstream in("input");
    int sum = 0;
    std::string line;

    std::vector<std::string> fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

    bool (*is_valid[])(std::string) = {byr, iyr, eyr, hgt, hcl, ecl, pid, cid};

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
                int colon = field.find(':');
                int num = std::find(fields.begin(), fields.end(), field.substr(0, colon)) - fields.begin();

                exists[num] = is_valid[num](field.substr(colon + 1));
                std::cout << "";
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