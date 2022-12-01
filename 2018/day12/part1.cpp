#include <iostream>
#include <fstream>
#include <map>
#include <array>

int main()
{
    std::map<int, bool> plants;

    std::ifstream in("input");
    std::string text;
    in >> text >> text >> text;

    int left = 0;
    int right = text.size();

    for (long unsigned int i = 0; i < text.size(); i++)
        plants[i] = text[i] == '#';

    std::array<bool, 32> end_value;

    while (in >> text)
    {
        int number = 0;

        for (auto c : text)
        {
            number *= 2;
            number += c == '#';
        }

        in >> text >> text;

        end_value[number] = text[0] == '#';
    }

    for (int i = 0; i < 20; i++)
    {
        std::map<int, bool> plants_new;
        int left_new = left, right_new = right;

        for (int pos = left - 2; pos < right + 2; pos++)
        {
            int number = 0;

            for (int check = pos - 2; check < pos + 3; check++)
            {
                number *= 2;
                number += plants[check];
            }

            plants_new[pos] = end_value[number];

            if (plants_new[pos] && left_new > pos)
                left_new = pos;

            if (plants_new[pos] && right_new < (pos + 1))
                right_new = pos + 1;

        }

        plants = plants_new;
        right = right_new;
        left = left_new;
    }

    int sum = 0;

    for (std::map<int, bool>::iterator it = plants.begin(); it != plants.end(); ++it)
        if (it->second)
            sum += it->first;

    std::cout << sum << '\n';

    return 0;
}