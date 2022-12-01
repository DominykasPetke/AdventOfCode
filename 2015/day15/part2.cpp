#include <fstream>
#include <iostream>
#include <vector>
#include <array>

class Ingredient
{
public:
    std::string name_;
    int capacity_, durability_, flavor_, texture_, calories_, used_;
};

long long int calc_points(std::vector<Ingredient> ingrs)
{
    std::array<int, 4> sums = {0, 0, 0, 0};

    int sum = 0;
    int cal_sum = 0;

    for (auto i : ingrs)
    {
        sum += i.used_;
        cal_sum += i.used_ * i.calories_;
        sums[0] += i.used_ * i.capacity_;
        sums[1] += i.used_ * i.durability_;
        sums[2] += i.used_ * i.flavor_;
        sums[3] += i.used_ * i.texture_;
    }

    if (sum != 100 || cal_sum != 500)
    {
        return -1;
    }

    long long int mult = 1;

    for (int i : sums)
    {
        if (i <= 0)
        {
            return 0;
        }
        else
        {
            mult *= i;
        }
    }

    //std::cout << mult << '\n';

    return mult;
}

int main()
{
    std::vector<Ingredient> ings;

    {
        std::ifstream in("input");
        std::string line;

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

            ings.push_back({values[0], std::stoi(values[2]), std::stoi(values[4]), std::stoi(values[6]), std::stoi(values[8]), std::stoi(values[10]), 1});
        }
    }

    long long int max = 0;

    for (int i = 1; i < 98; i++)
    {
        ings[0].used_ = i;

        for (int j = 1; j < 99 - i; j++)
        {
            ings[1].used_ = j;

            for (int k = 1; k < 100 - j - i; k++)
            {
                ings[2].used_ = k;
                ings[3].used_ = 100 - k - j - i;

                long long int pts = calc_points(ings);

                if (pts > max)
                {
                    max = pts;
                }
            }
        }
    }

    std::cout << max << '\n';

    return 0;
}