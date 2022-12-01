#include <iostream>
#include <fstream>
#include <tuple>

bool read(std::ifstream &in, std::tuple<int, int, int> &out)
{
    std::string text;

    if (in >> text)
    {
        std::get<0>(out) = std::stoi(text.substr(0, text.find('x')));
        text.erase(0, text.find('x') + 1);

        std::get<1>(out) = std::stoi(text.substr(0, text.find('x')));
        text.erase(0, text.find('x') + 1);

        std::get<2>(out) = std::stoi(text.substr(0, text.find('x')));

        return true;
    }
    else
        return false;
}

int main()
{
    std::ifstream in("input");

    std::tuple<int, int, int> data;
    int sum = 0;

    while (read(in, data))
    {
        int w1 = std::get<0>(data) * std::get<1>(data);
        int w2 = std::get<0>(data) * std::get<2>(data);
        int w3 = std::get<1>(data) * std::get<2>(data);

        int smallest = std::min(w1, std::min(w2, w3));

        sum += w1 * 2 + w2 * 2 + w3 * 2 + smallest;
    }

    std::cout << sum << '\n';

    return 0;
}