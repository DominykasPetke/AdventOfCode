#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <unordered_map>

int main()
{
    std::string line;
    std::ifstream in("input");

    std::getline(in, line);

    line = std::regex_replace(line, std::regex(","), " ");

    std::stringstream stream(line);

    int number;

    std::unordered_map<int, std::pair<int, int>> last_location;
    int turn_counter = 0;

    while (stream >> number)
    {
        last_location[number] = {++turn_counter, 0};
    }

    while (turn_counter < 2020)
    {
        number = last_location[number].second == 0 ? 0 : last_location[number].first - last_location[number].second;
        last_location[number] = {++turn_counter, last_location[number].first};
    }

    std::cout << number << '\n';

    return 0;
}